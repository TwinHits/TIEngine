#include "componentsystems/strategies/moves/MovesStrategy.h"

#include "managers/LogManager.h"
#include "utils/TIEMath.h"
#include "utils/constants/TIEMathConstants.h"

using namespace TIE;


void MovesStrategy::accelerate(const float delta, MovesComponent& movesComponent, PathsComponent& pathsComponent, PositionComponent& positionComponent) {
        float acceleration = movesComponent.acceleration * delta;
        if (pathsComponent.isOnLastPathPosition()) {
            float distanceToStop = Math::distanceToStop(movesComponent.speed, movesComponent.acceleration);
            float distanceToTarget = Math::distanceBetweenTwoPoints(positionComponent.position, *pathsComponent.peekNextPathPosition());
            if (distanceToTarget <= distanceToStop) {
                acceleration *= -1;
            }
        }

        float minimumSpeed = 0;
        movesComponent.speed += acceleration;
        movesComponent.speed = fmaxf(minimumSpeed, movesComponent.speed);
        movesComponent.speed = fminf(movesComponent.speed, movesComponent.targetSpeed);
}


void MovesStrategy::rotate(const float delta, MovesComponent& movesComponent, PathsComponent& pathsComponent, PositionComponent& positionComponent) {
    if (!Math::areFloatsEqual(movesComponent.targetRotation, positionComponent.rotation)) {

        float distance = movesComponent.rotationalVelocity.x * delta;
        float newRotation = positionComponent.rotation + distance;

        const float snapToRotationRadiusDelta = fabsf(movesComponent.rotationalVelocity.x * delta);
        if (Math::distanceBetweenTwoAngles(newRotation, movesComponent.targetRotation) <= snapToRotationRadiusDelta) {
            positionComponent.rotation = movesComponent.targetRotation;
        } else {
            positionComponent.rotation = newRotation;
        }
    }
}


bool MovesStrategy::move(const float delta, MovesComponent& movesComponent, PathsComponent& pathsComponent, PositionComponent& positionComponent) {
    if (pathsComponent.hasPath()) {

        const sf::Vector2f velocity = sf::Vector2f(movesComponent.speed, positionComponent.rotation);
        const sf::Vector2f distance = Math::translateVelocityByTime(velocity, delta);
        const sf::Vector2f newPosition = sf::Vector2f(positionComponent.position.x + distance.x, positionComponent.position.y + distance.y);

        const float snapToPositionRadius = fabsf(movesComponent.speed * delta);
        if (Math::distanceBetweenTwoPoints(newPosition, *pathsComponent.peekNextPathPosition()) <= snapToPositionRadius) {
            positionComponent.position = *pathsComponent.peekNextPathPosition();
            pathsComponent.popNextPathPosition();
            return true;
        } else {
            positionComponent.position = newPosition;
        }
    }
    return false;
}
