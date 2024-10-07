#include "componentsystems/strategies/AcceleratedTurnMovesStrategy.h"

#include <iostream>

#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "utils/TIEMath.h"
#include "utils/constants/TIEMathConstants.h"


using namespace TIE;

bool AcceleratedTurnMovesStrategy::execute(const float delta, TIEntity& tientity) {
    MovesComponent& movesComponent = MovesComponentSystem::Instance()->addComponent(tientity);
    PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);

    MovesComponentSystem::Instance()->setTargetRotation(movesComponent, positionComponent, tientity);

    this->accelerateRotation(delta, movesComponent, positionComponent);
    this->accelerate(delta, movesComponent, positionComponent);
    this->rotate(delta, movesComponent, positionComponent);
    return this->move(delta, movesComponent, positionComponent);
}


void AcceleratedTurnMovesStrategy::accelerateRotation(const float delta, MovesComponent& movesComponent, PositionComponent& positionComponent) {
    if (!MovesComponentSystem::Instance()->atTargetRotation(movesComponent, positionComponent)) {
        float rotationalAcceleration = movesComponent.rotationalAcceleration * delta * movesComponent.rotationalVelocity.y;

        float distanceToStop = Math::distanceToStop(movesComponent.rotationalVelocity.x, movesComponent.rotationalAcceleration);
        float distanceToTargetRotation = Math::distanceBetweenTwoAngles(positionComponent.rotation, movesComponent.targetRotation);
        if (distanceToTargetRotation <= distanceToStop) {
            rotationalAcceleration *= -1;
        }

        movesComponent.rotationalVelocity.x += rotationalAcceleration;
        movesComponent.rotationalVelocity.x = fmaxf(-movesComponent.targetRotationalSpeed, movesComponent.rotationalVelocity.x);
        movesComponent.rotationalVelocity.x = fminf(movesComponent.rotationalVelocity.x, movesComponent.targetRotationalSpeed);
    } else {
        movesComponent.rotationalVelocity.x = 0.0f;
    }
}


void AcceleratedTurnMovesStrategy::accelerate(const float delta, MovesComponent& movesComponent, PositionComponent& positionComponent) {
	if (!MovesComponentSystem::Instance()->atTargetPosition(movesComponent, positionComponent)) {
        float acceleration = movesComponent.acceleration * delta;
        if (movesComponent.isOnLastPathNode()) {
            float distanceToStop = Math::distanceToStop(movesComponent.speed, movesComponent.acceleration);
            float distanceToTarget = Math::distanceBetweenTwoPoints(positionComponent.position, movesComponent.getTargetPosition());
            if (distanceToTarget <= distanceToStop) {
                acceleration *= -1;
            }
        }

        // This used to be 1, I guess to allow inching forward to the distance if 
        // the math stops short.
        float minimumSpeed = 0;
        movesComponent.speed += acceleration;
        movesComponent.speed = fmaxf(minimumSpeed, movesComponent.speed);
        movesComponent.speed = fminf(movesComponent.speed, movesComponent.targetSpeed);
    } else {
        movesComponent.speed = 0.0f;
    }
}


void AcceleratedTurnMovesStrategy::rotate(const float delta, MovesComponent& movesComponent, PositionComponent& positionComponent) {
	if (!MovesComponentSystem::Instance()->atTargetRotation(movesComponent, positionComponent)) {
        float distance = movesComponent.rotationalVelocity.x * delta;
        float newRotation = positionComponent.rotation + distance;

        if (Math::areFloatsEqual(newRotation, movesComponent.targetRotation) ||
			Math::isAngleBetweenAngles(movesComponent.targetRotation, positionComponent.rotation, newRotation) ||
			Math::distanceBetweenTwoAngles(newRotation, movesComponent.targetRotation) < TIEMathConstants::FLOAT_COMPARISION_EPSILION
		) {
            positionComponent.rotation = movesComponent.targetRotation;
        } else {
            positionComponent.rotation = newRotation;
        }
	}
}


bool AcceleratedTurnMovesStrategy::move(const float delta, MovesComponent& movesComponent, PositionComponent& positionComponent) {
	if (movesComponent.speed > 0.0f) {
        sf::Vector2f velocity = sf::Vector2f(movesComponent.speed, positionComponent.rotation);
        sf::Vector2f distance = Math::translateVelocityByTime(velocity, delta);
        sf::Vector2f newPosition = sf::Vector2f(positionComponent.position.x + distance.x, positionComponent.position.y + distance.y);
        if (
            Math::areVectorsEqual(newPosition, movesComponent.getTargetPosition()) || 
            Math::isVectorBetweenVectors(positionComponent.position, newPosition, movesComponent.getTargetPosition()) || 
            Math::distanceBetweenTwoPoints(newPosition, movesComponent.getTargetPosition()) < TIEMathConstants::FLOAT_COMPARISION_EPSILION
		) {
            positionComponent.position = movesComponent.getTargetPosition();
            return true;
        } else {
            positionComponent.position = newPosition;
        }
    }
    return false;
}

