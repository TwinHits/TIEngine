#include "componentsystems/strategies/moves/AcceleratedTurnMovesStrategy.h"

#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/PathsComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "utils/TIEMath.h"
#include "utils/constants/TIEMathConstants.h"


using namespace TIE;

bool AcceleratedTurnMovesStrategy::execute(const float delta, TIEntity& tientity) {
    MovesComponent& movesComponent = MovesComponentSystem::Instance()->addComponent(tientity);
    PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);
    PathsComponent& pathsComponent = PathsComponentSystem::Instance()->addComponent(tientity);

    if (pathsComponent.hasPath()) {
        MovesComponentSystem::Instance()->setTargetRotation(movesComponent, positionComponent, tientity);

        this->accelerateRotation(delta, movesComponent, positionComponent);
        this->accelerate(delta, movesComponent, pathsComponent, positionComponent);
        this->rotate(delta, movesComponent, pathsComponent, positionComponent);
        return this->move(delta, movesComponent, pathsComponent, positionComponent);
    }
}


void AcceleratedTurnMovesStrategy::accelerateRotation(const float delta, MovesComponent& movesComponent, PositionComponent& positionComponent) {
    if (!Math::areFloatsEqual(movesComponent.targetRotation, positionComponent.rotation)) {
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
