#include "componentsystems/MovesComponentSystem.h" 

#include <cmath>
#include <memory>

#include "componentsystems/PathsComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
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
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(MovesComponentSystem::TARGET_ROTATION, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(MovesComponentSystem::AT_ROTATION, this);

	this->atDestinationMessageSubscription = MessageManager::Instance()->getSubscriptionId("AtDestination");
}


void MovesComponentSystem::update(const float delta) {
	for (auto& c : components) {
		if (c.pathsComponent.hasPath()) {
			c.movesComponent.movesStrategy->execute(delta, c.tientity);
		}
	}
}


MovesComponent& MovesComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<MovesComponent>()) {
        MovesComponent& movesComponent = tientity.addComponent<MovesComponent>();
        PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);
        PathsComponent& pathsComponent = PathsComponentSystem::Instance()->addComponent(tientity);
        this->components.push_back({ 
			movesComponent, 
			positionComponent, 
			pathsComponent, 
			tientity,
		});
        return movesComponent;
	} else {
		return *tientity.getComponent<MovesComponent>();
	}
}


MovesComponent& MovesComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
    MovesComponent& movesComponent = this->addComponent(tientity);
	PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);
	const ScriptTableReader& reader = factory.getReader().getReader(MovesComponentSystem::MOVES);

	const std::string& strategyName = reader.get<std::string>(MovesComponentSystem::STRATEGY, SnapTurnMovesStrategy::NAME);
	this->assignMovesStrategyByName(movesComponent, strategyName);

	const float& targetSpeed = reader.get<float>(MovesComponentSystem::SPEED, movesComponent.targetSpeed);
	const float& acceleration = reader.get<float>(MovesComponentSystem::ACCELERATION, movesComponent.acceleration);

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
    } else if (key == MovesComponentSystem::ROTATIONAL_ACCELERATION) {
        movesComponent.rotationalAcceleration = value;
    }
}


sol::object MovesComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
	MovesComponent* component = tientity.getComponent<MovesComponent>();
	if (component != nullptr) {
		if (key == MovesComponentSystem::AT_ROTATION) {
			return ScriptManager::Instance()->getObjectFromValue(this->atTargetRotation(tientity));
		} else if (key == MovesComponentSystem::SPEED) {
			return ScriptManager::Instance()->getObjectFromValue(component->speed);
		} else if (key == MovesComponentSystem::ROTATIONAL_SPEED) {
			return ScriptManager::Instance()->getObjectFromValue(component->rotationalVelocity.x);
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
	PathsComponent& pathsComponent = PathsComponentSystem::Instance()->addComponent(tientity);
    float parentWorldRotation = 0;
    if (tientity.getParent().hasComponent<PositionComponent>()) {
        parentWorldRotation = tientity.getParent().getComponent<PositionComponent>()->worldRotation;
    }
    movesComponent.targetRotation = Math::angleBetweenTwoPoints(positionComponent.worldPosition, *pathsComponent.peekNextPathPosition()) - parentWorldRotation;
    this->setTargetRotationDirection(movesComponent, positionComponent);
}


void MovesComponentSystem::setTargetRotationDirection(MovesComponent& movesComponent, PositionComponent& positionComponent) {
    movesComponent.rotationalVelocity.y = Math::directionFromAngleToAngle(positionComponent.rotation, movesComponent.targetRotation);
}


bool MovesComponentSystem::atTargetRotation(TIEntity& tientity) {
    MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
    PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
    if (movesComponent != nullptr && positionComponent != nullptr) {
		return Math::areFloatsEqual(movesComponent->targetRotation, positionComponent->rotation);
	} else {
		return false;
	}
}
