#include "componentsystems/MovesComponentSystem.h" 

#include <cmath>
#include <string>

#include <SFML/Graphics.hpp>

#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/GridComponentSystem.h"
#include "managers/LogManager.h" 
#include "managers/WorldManager.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"
#include "utils/ComponentSystems.h"
#include "utils/TIEMath.h"
#include "utils/types/ComponentSystemsTypes.h"

using namespace TIE;

void MovesComponentSystem::update(const float delta) {
	for (auto& c : components) {

		if (c.movesComponent.hasTargetPosition) {
			this->accelerate(c.movesComponent, c.positionComponent, delta);
			this->move(c.movesComponent, c.positionComponent, delta);

			if (c.movesComponent.rotates) {
				this->setTargetRotation(c.movesComponent, c.positionComponent);
				this->accelerateRotation(c.movesComponent, c.positionComponent, delta);
				this->rotate(c.movesComponent, c.positionComponent, delta);
			}
		}
	}
}


MovesComponent& MovesComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<MovesComponent>()) {
        MovesComponent& movesComponent = tientity.addComponent<MovesComponent>();
        PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);
        this->components.push_back({ movesComponent, positionComponent });
        return movesComponent;
	} else {
		return *tientity.getComponent<MovesComponent>();
	}
}


MovesComponent& MovesComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
    MovesComponent& movesComponent = this->addComponent(tientity);
    PositionComponent& positionComponent = tientity.addComponent<PositionComponent>();

	float targetSpeed = ComponentSystems::getFactoryValue<float>(factory, MovesComponentSystem::SPEED, movesComponent.targetSpeed, tientity);
	float acceleration = ComponentSystems::getFactoryValue<float>(factory, MovesComponentSystem::ACCELERATION, movesComponent.acceleration, tientity);
	float deceleration = ComponentSystems::getFactoryValue<float>(factory, MovesComponentSystem::ACCELERATION, movesComponent.deceleration, tientity);

	float rotates = ComponentSystems::getFactoryValue<bool>(factory, MovesComponentSystem::ROTATES, movesComponent.rotates, tientity);
	float targetRotationalSpeed = ComponentSystems::getFactoryValue<float>(factory, MovesComponentSystem::ROTATIONAL_SPEED, movesComponent.targetRotationalSpeed, tientity);
	float rotationalAcceleraton = ComponentSystems::getFactoryValue<float>(factory, MovesComponentSystem::ROTATIONAL_ACCELERATION, movesComponent.rotationalAcceleration, tientity);
	float targetRotation = ComponentSystems::getFactoryValue<float>(factory, MovesComponentSystem::ROTATION, movesComponent.targetRotation, tientity);

    movesComponent.targetSpeed = targetSpeed;
    movesComponent.acceleration = acceleration;
    movesComponent.deceleration = deceleration;

	movesComponent.rotates = rotates;
	movesComponent.targetRotation = targetRotation;
	movesComponent.targetRotationalSpeed = targetRotationalSpeed;
	movesComponent.rotationalAcceleration = rotationalAcceleraton;
	
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


const std::string& MovesComponentSystem::getName() {
	return MovesComponentSystem::MOVES;
}


bool MovesComponentSystem::setComponentProperty(const std::string& key, bool value, TIEntity& tientity) {
    MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	if (movesComponent != nullptr) {
		if (key == MovesComponentSystem::ROTATES) {
			movesComponent->rotates = value;
		}
	}
    return false;
}


bool MovesComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity)  {
    MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
    if (movesComponent != nullptr) {
        if (key == MovesComponentSystem::SPEED) {
			movesComponent->targetSpeed = value;
		} else if (key == MovesComponentSystem::ACCELERATION) {
			movesComponent->acceleration = value;
		} else if (key == MovesComponentSystem::ROTATIONAL_SPEED) {
			movesComponent->rotationalVelocity.x = value;
		} else if (key == MovesComponentSystem::ROTATION) {
			movesComponent->targetRotation = value;
		} else if (key == MovesComponentSystem::DESTINATION) {
			this->setTargetPosition(tientity, value);
		} else if (key == MovesComponentSystem::ROTATIONAL_ACCELERATION) {
			movesComponent->rotationalAcceleration = value;
		}
    }
    return false;
}


bool MovesComponentSystem::setComponentProperty(const std::string& key, const sf::Vector2f& value, TIEntity& tientity)  {
	MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	if (movesComponent != nullptr) {
		if (key == MovesComponentSystem::DESTINATION) {
			this->setTargetPosition(tientity, value);
		}
	}
	return false;
}


bool MovesComponentSystem::setComponentProperty(const std::string& key, const sf::Vector2i& value, TIEntity& tientity) {
	MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	if (movesComponent != nullptr) {
		if (key == MovesComponentSystem::DESTINATION) {
			this->setTargetPosition(tientity, sf::Vector2f(value.x, value.y));
		}
	}
	return false;
}


sol::object MovesComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
	MovesComponent* component = tientity.getComponent<MovesComponent>();
	if (component != nullptr) {
		if (key == MovesComponentSystem::AT_DESTINATION) {
			return ScriptManager::Instance()->getObjectFromValue(this->atTargetPosition(tientity));
		} else if (key == MovesComponentSystem::SPEED) {
			return ScriptManager::Instance()->getObjectFromValue(component->speed);
		} else if (key == MovesComponentSystem::ROTATIONAL_SPEED) {
			return ScriptManager::Instance()->getObjectFromValue(component->rotationalVelocity.x);
		} else if (key == MovesComponentSystem::DESTINATION) {
			return ScriptManager::Instance()->getObjectFromValue(component->targetPosition);
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


ComponentSystems::ComponentSystemPropertiesMap& MovesComponentSystem::populateComponentSystemsPropertiesMap(ComponentSystems::ComponentSystemPropertiesMap& map) {
	ComponentSystems::insertComponentPropertyIntoMap(MovesComponentSystem::SPEED, map);
	ComponentSystems::insertComponentPropertyIntoMap(MovesComponentSystem::ACCELERATION, map);
	ComponentSystems::insertComponentPropertyIntoMap(MovesComponentSystem::DECELERATION, map);
	ComponentSystems::insertComponentPropertyIntoMap(MovesComponentSystem::ROTATES, map);
	ComponentSystems::insertComponentPropertyIntoMap(MovesComponentSystem::ROTATIONAL_SPEED, map);
	ComponentSystems::insertComponentPropertyIntoMap(MovesComponentSystem::ROTATION, map);
	ComponentSystems::insertComponentPropertyIntoMap(MovesComponentSystem::DESTINATION, map);
	ComponentSystems::insertComponentPropertyIntoMap(MovesComponentSystem::AT_DESTINATION, map);
	ComponentSystems::insertComponentPropertyIntoMap(MovesComponentSystem::TARGET_ROTATION, map);
	ComponentSystems::insertComponentPropertyIntoMap(MovesComponentSystem::ROTATIONAL_ACCELERATION, map);
	return map;
}


void MovesComponentSystem::setTargetPosition(TIEntity& tientity, const sf::Vector2f& targetPosition) {
	MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
	if (movesComponent != nullptr && positionComponent != nullptr) {

		sf::Vector2f normalizedPosition = targetPosition;
		if (WorldManager::Instance()->isGridConfigured()) {
			normalizedPosition = GridComponentSystem::Instance()->normalizePositionToGrid(targetPosition);
		}

		movesComponent->targetPosition = normalizedPosition;
		movesComponent->hasTargetPosition = true;

	}
}


void MovesComponentSystem::setTargetPosition(TIEntity& tientity, float distance) {
	MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
	if (movesComponent != nullptr && positionComponent != nullptr) {

		sf::Vector2f velocity = sf::Vector2f(distance, positionComponent->rotation);
		sf::Vector2f distance = Math::translateVelocityByTime(velocity,  1);
		sf::Vector2f destination = sf::Vector2f(positionComponent->position.x + distance.x, positionComponent->position.y + distance.y);

		MovesComponentSystem::Instance()->setTargetPosition(tientity, destination);
	}
}


void MovesComponentSystem::setTargetRotation(MovesComponent& movesComponent, PositionComponent& positionComponent) {
	if (!this->atTargetPosition(movesComponent, positionComponent)) {
		movesComponent.targetRotation = Math::angleBetweenTwoPoints(positionComponent.position, movesComponent.targetPosition);
        movesComponent.rotationalVelocity.y = Math::directionFromAngleToAngle(positionComponent.rotation, movesComponent.targetRotation);
		movesComponent.hasTargetRotation = true;
	}
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
	bool result = Math::areVectorsEqual(movesComponent.targetPosition, positionComponent.position);
	if (result) {
		movesComponent.hasTargetPosition = false;
	}
	return result;
}


bool MovesComponentSystem::atTargetSpeed(MovesComponent& movesComponent) {
	return Math::areFloatsEqual(movesComponent.speed, movesComponent.targetSpeed);
}


bool MovesComponentSystem::atTargetRotation(MovesComponent& movesComponent, PositionComponent& positionComponent) {
	return Math::areFloatsEqual(movesComponent.targetRotation, positionComponent.rotation);
}


void MovesComponentSystem::accelerate(MovesComponent& movesComponent, PositionComponent& positionComponent, const float delta) {
	if (!this->atTargetPosition(movesComponent, positionComponent)) {
		if (Math::areFloatsEqual(movesComponent.acceleration, 0.0f) && Math::areFloatsEqual(movesComponent.deceleration, 0.0f)) {
			movesComponent.speed = movesComponent.targetSpeed;
		} else {

            float acceleration = movesComponent.acceleration;
            float minimumSpeed = movesComponent.targetSpeed / movesComponent.targetSpeed;
			if (movesComponent.deceleration > 0.0f) {
				float distanceToStop = (movesComponent.speed / movesComponent.deceleration) * movesComponent.speed;
				float distanceToTarget = Math::distanceBetweenTwoPoints(positionComponent.position, movesComponent.targetPosition);
				if (distanceToTarget <= distanceToStop) {
					acceleration = -movesComponent.deceleration;
				}
			}

            // Set speed according to delta, don't go below minimum or above target
            movesComponent.speed += acceleration * delta;
            movesComponent.speed = fmaxf(minimumSpeed, movesComponent.speed);
            movesComponent.speed = fminf(movesComponent.speed, movesComponent.targetSpeed);
		}
	} else {
		movesComponent.speed = 0.0f; // Fallback to zero
	}
}


void MovesComponentSystem::accelerateRotation(MovesComponent& movesComponent, PositionComponent& positionComponent, const float delta) {
	if (!this->atTargetRotation(movesComponent, positionComponent) && !this->atTargetPosition(movesComponent, positionComponent)) {
        if (Math::areFloatsEqual(movesComponent.rotationalAcceleration, 0.0f)) {
            movesComponent.rotationalVelocity.x = movesComponent.targetRotationalSpeed * movesComponent.rotationalVelocity.y;
        } else {
            float rotationalAcceleration = movesComponent.rotationalAcceleration * movesComponent.rotationalVelocity.y;
            float minimumSpeed = -movesComponent.targetRotationalSpeed;

            float distanceToStop = fabsf((movesComponent.rotationalVelocity.x / movesComponent.rotationalAcceleration) * movesComponent.rotationalVelocity.x);
            float rotationDistanceToTarget = Math::distanceBetweenTwoAngles(positionComponent.rotation, movesComponent.targetRotation);
            if (rotationDistanceToTarget <= distanceToStop) {
                rotationalAcceleration = -movesComponent.rotationalAcceleration * movesComponent.rotationalVelocity.y;
            }

            movesComponent.rotationalVelocity.x += rotationalAcceleration * delta;
            movesComponent.rotationalVelocity.x = fmaxf(minimumSpeed, movesComponent.rotationalVelocity.x);
            movesComponent.rotationalVelocity.x = fminf(movesComponent.rotationalVelocity.x, movesComponent.targetRotationalSpeed);
        }
    } else {
        movesComponent.rotationalVelocity.x = 0.0f;
    }
}


void MovesComponentSystem::rotate(MovesComponent& movesComponent, PositionComponent& positionComponent, const float delta) {
	if (!this->atTargetRotation(movesComponent, positionComponent)) {
        float distance = movesComponent.rotationalVelocity.x * delta;
        float newRotation = positionComponent.rotation + distance;
        if (!Math::isAngleBetweenAngles(movesComponent.targetRotation, positionComponent.rotation, newRotation)) {
            positionComponent.rotation = newRotation;
        } else {
            positionComponent.rotation = movesComponent.targetRotation;
        }
	}
} 


void MovesComponentSystem::move(MovesComponent& movesComponent, PositionComponent& positionComponent, const float delta) {
	if (movesComponent.speed > 0.0f) {
        sf::Vector2f velocity = sf::Vector2f(movesComponent.speed, positionComponent.rotation);
        sf::Vector2f distance = Math::translateVelocityByTime(velocity, delta);
        sf::Vector2f newPosition = sf::Vector2f(positionComponent.position.x + distance.x, positionComponent.position.y + distance.y);
        if (Math::areVectorsEqual(newPosition, movesComponent.targetPosition) || 
			Math::isVectorBetweenVectors(positionComponent.position, newPosition, movesComponent.targetPosition) || 
			Math::distanceBetweenTwoPoints(newPosition, movesComponent.targetPosition) < 1.0f
		) {
            positionComponent.position = movesComponent.targetPosition;
        } else {
            positionComponent.position = newPosition;
        }
    }
}

