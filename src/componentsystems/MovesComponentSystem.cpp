#include "componentsystems/MovesComponentSystem.h" 

#include <cmath>
#include <memory>
#include <queue>

#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/GridComponentSystem.h"
#include "componentsystems/MessagesComponentSystem.h"
#include "componentsystems/WireframeComponentSystem.h"
#include "componentsystems/strategies/moves/AcceleratedTurnMovesStrategy.h"
#include "componentsystems/strategies/moves/SnapTurnMovesStrategy.h"
#include "componentsystems/strategies/moves/SteadyMovesStrategy.h"
#include "managers/ComponentSystemsManager.h"
#include "managers/MessageManager.h"
#include "managers/ScriptManager.h"
#include "managers/WorldManager.h"
#include "utils/TIEMath.h"

using namespace TIE;

MovesComponentSystem::MovesComponentSystem() {
	this->name = MovesComponentSystem::MOVES;
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(MovesComponentSystem::STRATEGY, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(MovesComponentSystem::SPEED, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(MovesComponentSystem::ACCELERATION, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(MovesComponentSystem::ROTATES, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(MovesComponentSystem::ROTATIONAL_SPEED, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(MovesComponentSystem::ROTATIONAL_ACCELERATION, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(MovesComponentSystem::DESTINATION, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(MovesComponentSystem::DESTINATION_PATH, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(MovesComponentSystem::DESTINATION_X, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(MovesComponentSystem::DESTINATION_Y, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(MovesComponentSystem::AT_DESTINATION, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(MovesComponentSystem::TARGET_ROTATION, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(MovesComponentSystem::AT_ROTATION, this);

	this->atDestinationMessageSubscription = MessageManager::Instance()->getSubscriptionId("AtDestination");
}


void MovesComponentSystem::update(const float delta) {
	for (auto& c : components) {
		if (!this->atTargetPosition(c.movesComponent, c.positionComponent)) {
			bool atTargetPosition = c.movesComponent.movesStrategy->execute(delta, c.tientity);
			if (atTargetPosition) {
				MessagesComponentSystem::Instance()->sendMessage(Message(this->atDestinationMessageSubscription, c.tientity.getId(), c.tientity.getId()));
			}
		}
	}
}


MovesComponent& MovesComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<MovesComponent>()) {
        MovesComponent& movesComponent = tientity.addComponent<MovesComponent>();
        PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);
        this->components.push_back({ movesComponent, positionComponent, tientity });
        return movesComponent;
	} else {
		return *tientity.getComponent<MovesComponent>();
	}
}


MovesComponent& MovesComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
    MovesComponent& movesComponent = this->addComponent(tientity);
	PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);
	const ScriptTableReader& reader = factory.getReader().getReader(MovesComponentSystem::MOVES);

	const std::string& strategyName = reader.get<std::string>(MovesComponentSystem::STRATEGY, "SnapTurn");
	this->assignMovesStrategyByName(movesComponent, strategyName);

	const float& targetSpeed = reader.get<float>(MovesComponentSystem::SPEED, movesComponent.targetSpeed);
	const float& acceleration = reader.get<float>(MovesComponentSystem::ACCELERATION, movesComponent.acceleration);

	if (reader.hasKey(MovesComponentSystem::DESTINATION)) {
		const ScriptTableReader& destinationReader = reader.getReader(MovesComponentSystem::DESTINATION);
		float destinationX = destinationReader.get<float>(MovesComponentSystem::DESTINATION_X, 0);
		float destinationY = destinationReader.get<float>(MovesComponentSystem::DESTINATION_Y, 0);
		if (!destinationX) {
			destinationX = positionComponent.position.x;
		}
		if (!destinationY) {
			destinationY = positionComponent.position.y;
		}
		this->setTargetPosition(movesComponent, positionComponent, sf::Vector2f(destinationX, destinationY), tientity);
	}

	const float& targetRotationalSpeed = reader.get<float>(MovesComponentSystem::ROTATIONAL_SPEED, movesComponent.targetRotationalSpeed);
	const float& rotationalAcceleraton = reader.get<float>(MovesComponentSystem::ROTATIONAL_ACCELERATION, movesComponent.rotationalAcceleration);
	const float& targetRotation = reader.get<float>(MovesComponentSystem::TARGET_ROTATION, positionComponent.rotation);

    movesComponent.targetSpeed = targetSpeed;
    movesComponent.acceleration = acceleration;

	movesComponent.targetRotation = Math::normalizeAngleDegrees(targetRotation);
	movesComponent.targetRotationalSpeed = targetRotationalSpeed;
	movesComponent.rotationalAcceleration = rotationalAcceleraton;
	this->setTargetRotationDirection(movesComponent, positionComponent);
	
	return movesComponent;
}


bool MovesComponentSystem::removeComponent(TIEntity& tientity) {
	MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	if (movesComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->movesComponent == movesComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<MovesComponent>();
	} else {
		return false;
	}
}


void MovesComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity)  {
    MovesComponent& movesComponent = this->addComponent(tientity);
    if (key == MovesComponentSystem::SPEED) {
        movesComponent.targetSpeed = value;
    } else if (key == MovesComponentSystem::ACCELERATION) {
        movesComponent.acceleration = value;
    } else if (key == MovesComponentSystem::ROTATIONAL_SPEED) {
        movesComponent.rotationalVelocity.x = value;
    } else if (key == MovesComponentSystem::TARGET_ROTATION) {
		movesComponent.targetRotation = Math::normalizeAngleDegrees(value);
        this->setTargetRotationDirection(movesComponent, *tientity.getComponent<PositionComponent>());
    } else if (key == MovesComponentSystem::DESTINATION) {
        this->setTargetPosition(tientity, value);
    } else if (key == MovesComponentSystem::DESTINATION_X) {
		if (movesComponent.hasTargetPosition()) {
			this->setTargetPosition(tientity, sf::Vector2f(value, movesComponent.getTargetPosition().y));
		} else {
			PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);
			this->setTargetPosition(tientity, sf::Vector2f(value, positionComponent.worldPosition.y));
		}
    } else if (key == MovesComponentSystem::DESTINATION_Y) {
		if (movesComponent.hasTargetPosition()) {
			this->setTargetPosition(tientity, sf::Vector2f(movesComponent.getTargetPosition().x, value));
		} else {
			PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);
			this->setTargetPosition(tientity, sf::Vector2f(positionComponent.worldPosition.x, value));
		}
    } else if (key == MovesComponentSystem::ROTATIONAL_ACCELERATION) {
        movesComponent.rotationalAcceleration = value;
    }
}


void MovesComponentSystem::setComponentProperty(const std::string& key, const sf::Vector2f& value, TIEntity& tientity)  {
	MovesComponent& movesComponent = this->addComponent(tientity);
    if (key == MovesComponentSystem::DESTINATION) {
        this->setTargetPosition(tientity, value);
    }
}


void MovesComponentSystem::setComponentProperty(const std::string& key, const std::vector<sf::Vector2f>& value, TIEntity& tientity) {
	MovesComponent& movesComponent = this->addComponent(tientity);
    if (key == MovesComponentSystem::DESTINATION_PATH) {
		movesComponent.path = std::queue<sf::Vector2f>();
		for (auto& point : value) {
			movesComponent.path.push(point);
		}
    }
}


void MovesComponentSystem::setComponentProperty(const std::string& key, const sf::Vector2i& value, TIEntity& tientity) {
	MovesComponent& movesComponent = this->addComponent(tientity);
    if (key == MovesComponentSystem::DESTINATION) {
        this->setTargetPosition(tientity, sf::Vector2f(value.x, value.y));
    }
}


sol::object MovesComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
	MovesComponent* component = tientity.getComponent<MovesComponent>();
	if (component != nullptr) {
		if (key == MovesComponentSystem::AT_DESTINATION) {
			return ScriptManager::Instance()->getObjectFromValue(this->atTargetPosition(tientity));
		} else if (key == MovesComponentSystem::AT_ROTATION) {
			return ScriptManager::Instance()->getObjectFromValue(this->atTargetRotation(tientity));
		} else if (key == MovesComponentSystem::SPEED) {
			return ScriptManager::Instance()->getObjectFromValue(component->speed);
		} else if (key == MovesComponentSystem::ROTATIONAL_SPEED) {
			return ScriptManager::Instance()->getObjectFromValue(component->rotationalVelocity.x);
		} else if (key == MovesComponentSystem::DESTINATION) {
			if (component->hasTargetPosition()) {
				return ScriptManager::Instance()->getObjectFromValue(component->getTargetPosition());
			} else {
				PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);
				return ScriptManager::Instance()->getObjectFromValue(positionComponent.worldPosition);
			}
		} else if (key == MovesComponentSystem::TARGET_ROTATION) {
			return ScriptManager::Instance()->getObjectFromValue(component->targetRotation);
		} else if (key == MovesComponentSystem::ROTATIONAL_ACCELERATION) {
			return ScriptManager::Instance()->getObjectFromValue(component->rotationalAcceleration);
		} else if (key == MovesComponentSystem::ROTATIONAL_SPEED) {
			return ScriptManager::Instance()->getObjectFromValue(component->targetRotationalSpeed);
		}
	}
	return ScriptManager::Instance()->getObjectFromValue(nullptr);
}


void MovesComponentSystem::setTargetPosition(TIEntity& tientity, float distance) {
	MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
	if (movesComponent != nullptr && positionComponent != nullptr) {

		sf::Vector2f velocity = sf::Vector2f(distance, positionComponent->rotation);
		sf::Vector2f distance = Math::translateVelocityByTime(velocity,  1);
		sf::Vector2f destination = sf::Vector2f(positionComponent->position.x + distance.x, positionComponent->position.y + distance.y);

		this->setTargetPosition(*movesComponent, *positionComponent, destination, tientity);
	}
}


void MovesComponentSystem::setTargetPosition(TIEntity& tientity, const sf::Vector2f& targetPosition) {
	MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
	if (movesComponent != nullptr && positionComponent != nullptr) {
		return this->setTargetPosition(*movesComponent, *positionComponent, targetPosition, tientity);
	}
}


void MovesComponentSystem::setTargetPosition(MovesComponent& movesComponent, PositionComponent& positionComponent, const sf::Vector2f& targetPosition, TIEntity& tientity) {
    sf::Vector2f normalizedPosition = targetPosition;
    if (WorldManager::Instance()->isGridConfigured()) {
        normalizedPosition = GridComponentSystem::Instance()->normalizePositionToGrid(targetPosition);
    }

    movesComponent.path = {};
    movesComponent.path.push(normalizedPosition);
    this->setTargetRotation(movesComponent, positionComponent, tientity);
}


void MovesComponentSystem::assignMovesStrategyByName(MovesComponent& movesComponent, const std::string& strategyName) {
	if (strategyName == SnapTurnMovesStrategy::NAME) {
		movesComponent.movesStrategy = std::make_unique<SnapTurnMovesStrategy>();
	} else if (strategyName == AcceleratedTurnMovesStrategy::NAME) {
		movesComponent.movesStrategy = std::make_unique<AcceleratedTurnMovesStrategy>();
	} else if (strategyName == SteadyMovesStrategy::NAME) {
		movesComponent.movesStrategy = std::make_unique<SteadyMovesStrategy>();
	}
}


void MovesComponentSystem::setTargetRotation(MovesComponent& movesComponent, PositionComponent& positionComponent, TIEntity& tientity) {
	if (movesComponent.hasTargetPosition()) {
		float parentWorldRotation = 0;
		if (tientity.getParent().hasComponent<PositionComponent>()) {
			parentWorldRotation = tientity.getParent().getComponent<PositionComponent>()->worldRotation;
		}
		movesComponent.targetRotation = Math::angleBetweenTwoPoints(positionComponent.worldPosition, movesComponent.getTargetPosition()) - parentWorldRotation;
		this->setTargetRotationDirection(movesComponent, positionComponent);
	}
}


void MovesComponentSystem::setTargetRotationDirection(MovesComponent& movesComponent, PositionComponent& positionComponent) {
    movesComponent.rotationalVelocity.y = Math::directionFromAngleToAngle(positionComponent.rotation, movesComponent.targetRotation);
}


bool MovesComponentSystem::atTargetPosition(TIEntity& tientity) {
    MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
    PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
    if (movesComponent != nullptr && positionComponent != nullptr) {
		return this->atTargetPosition(*movesComponent, *positionComponent);
	} else {
		return false;
	}
}


bool MovesComponentSystem::atTargetPosition(MovesComponent& movesComponent, PositionComponent& positionComponent) {
	if (movesComponent.hasTargetPosition() && Math::areVectorsEqual(movesComponent.getTargetPosition(), positionComponent.position)) {
		movesComponent.path.pop();
	}
	return !movesComponent.hasTargetPosition();
}


bool MovesComponentSystem::atTargetSpeed(MovesComponent& movesComponent) {
	return Math::areFloatsEqual(movesComponent.speed, movesComponent.targetSpeed);
}


bool MovesComponentSystem::atTargetRotation(TIEntity& tientity) {
    MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
    PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
    if (movesComponent != nullptr && positionComponent != nullptr) {
		return this->atTargetRotation(*movesComponent, *positionComponent);
	} else {
		return false;
	}
}


bool MovesComponentSystem::atTargetRotation(MovesComponent& movesComponent, PositionComponent& positionComponent) {
	return Math::areFloatsEqual(movesComponent.targetRotation, positionComponent.rotation);
}


std::pair<GlobalId, GlobalId> MovesComponentSystem::addWireframe(TIEntity& tientity) {
	MovesComponent& movesComponent = this->addComponent(tientity);
	PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);

	const sf::Vector2f origin = sf::Vector2f(0, 0);
	float distanceToTargetPosition = 0;
    sf::FloatRect bounds = sf::FloatRect(0, 0, 0, 0);
    float angleToTargetPosition = 0;
    if (movesComponent.hasTargetPosition()) {
        const sf::Vector2f& targetPosition = movesComponent.getTargetPosition();
		distanceToTargetPosition = Math::distanceBetweenTwoPoints(positionComponent.worldPosition, targetPosition);
		bounds = sf::FloatRect(0, 0, distanceToTargetPosition, 0);
        angleToTargetPosition = Math::angleBetweenTwoPoints(positionComponent.worldPosition, targetPosition);
	}
	return WireframeComponentSystem::Instance()->createWireframe(tientity, bounds, origin, angleToTargetPosition);
}
