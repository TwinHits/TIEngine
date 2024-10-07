#include "componentsystems/strategies/SnapTurnMovesStrategy.h"

#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "utils/TIEMath.h"
#include "utils/constants/TIEMathConstants.h"

using namespace TIE;

bool SnapTurnMovesStrategy::execute(const float delta, TIEntity& tientity) {
    MovesComponent& movesComponent = MovesComponentSystem::Instance()->addComponent(tientity);
    PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);

    MovesComponentSystem::Instance()->setTargetRotation(movesComponent, positionComponent, tientity);

    this->accelerate(delta, movesComponent, positionComponent);
    this->rotate(delta, movesComponent, positionComponent);
    return this->move(delta, movesComponent, positionComponent);
}


void SnapTurnMovesStrategy::accelerate(const float delta, MovesComponent& movesComponent, PositionComponent& positionComponent) {
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
    }
    else {
        movesComponent.speed = 0.0f;
    }
}


void SnapTurnMovesStrategy::rotate(const float delta, MovesComponent& movesComponent, PositionComponent& positionComponent) {
    positionComponent.rotation = movesComponent.targetRotation;
}


bool SnapTurnMovesStrategy::move(const float delta, MovesComponent& movesComponent, PositionComponent& positionComponent) {
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
        }
        else {
            positionComponent.position = newPosition;
        }
    }
    return false;
}

