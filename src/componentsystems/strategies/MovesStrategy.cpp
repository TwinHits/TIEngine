#include "componentsystems/strategies/MovesStrategy.h"

#include "componentsystems/MovesComponentSystem.h"
#include "managers/SceneManager.h"
#include "utils/TIEMath.h"
#include "utils/constants/TIEMathConstants.h"

using namespace TIE;


void MovesStrategy::accelerate(const float delta, MovesComponent& movesComponent, PositionComponent& positionComponent) {
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
        // the stopping distance math is short.
        float minimumSpeed = 0;
        movesComponent.speed += acceleration;
        movesComponent.speed = fmaxf(minimumSpeed, movesComponent.speed);
        movesComponent.speed = fminf(movesComponent.speed, movesComponent.targetSpeed);
    }
    else {
        movesComponent.speed = 0.0f;
    }
}


void MovesStrategy::rotate(const float delta, MovesComponent& movesComponent, PositionComponent& positionComponent) {
    if (!MovesComponentSystem::Instance()->atTargetRotation(movesComponent, positionComponent)) {

        float distance = movesComponent.rotationalVelocity.x * delta;
        float newRotation = positionComponent.rotation + distance;

        const float snapToRotationRadius = fabsf(movesComponent.rotationalVelocity.x / SceneManager::Instance()->getFPS());
        if (Math::distanceBetweenTwoAngles(newRotation, movesComponent.targetRotation) <= snapToRotationRadius) {
            positionComponent.rotation = movesComponent.targetRotation;
        } else {
            positionComponent.rotation = newRotation;
        }
    }
}


bool MovesStrategy::move(const float delta, MovesComponent& movesComponent, PositionComponent& positionComponent) {
    if (movesComponent.speed > 0.0f) {

        const sf::Vector2f velocity = sf::Vector2f(movesComponent.speed, positionComponent.rotation);
        const sf::Vector2f distance = Math::translateVelocityByTime(velocity, delta);
        const sf::Vector2f newPosition = sf::Vector2f(positionComponent.position.x + distance.x, positionComponent.position.y + distance.y);

        const float snapToPositionRadius = fabsf(movesComponent.speed / SceneManager::Instance()->getFPS());
        if (Math::distanceBetweenTwoPoints(newPosition, movesComponent.getTargetPosition()) <= snapToPositionRadius) {
            positionComponent.position = movesComponent.getTargetPosition();
            return true;
        } else {
            positionComponent.position = newPosition;
        }
    }
    return false;
}
