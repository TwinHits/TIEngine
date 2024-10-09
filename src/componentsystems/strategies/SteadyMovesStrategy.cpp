#include "componentsystems/strategies/SteadyMovesStrategy.h"

#include <iostream>

#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "utils/TIEMath.h"
#include "utils/constants/TIEMathConstants.h"


using namespace TIE;

bool SteadyMovesStrategy::execute(const float delta, TIEntity& tientity) {
    MovesComponent& movesComponent = MovesComponentSystem::Instance()->addComponent(tientity);
    PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);

    MovesComponentSystem::Instance()->setTargetRotation(movesComponent, positionComponent, tientity);

    this->accelerate(delta, movesComponent, positionComponent);
    this->accelerateRotation(delta, movesComponent, positionComponent);
    this->rotate(delta, movesComponent, positionComponent);
    return this->move(delta, movesComponent, positionComponent);
}


void SteadyMovesStrategy::accelerate(const float delta, MovesComponent& movesComponent, PositionComponent& positionComponent) {
    movesComponent.speed = movesComponent.targetSpeed;

}


void SteadyMovesStrategy::accelerateRotation(const float delta, MovesComponent& movesComponent, PositionComponent& positionComponent) {
    movesComponent.rotationalVelocity.x = movesComponent.targetRotationalSpeed;

}

