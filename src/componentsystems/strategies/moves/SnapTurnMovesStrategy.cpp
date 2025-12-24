#include "componentsystems/strategies/moves/SnapTurnMovesStrategy.h"

#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/PathsComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "utils/TIEMath.h"
#include "utils/constants/TIEMathConstants.h"

using namespace TIE;

bool SnapTurnMovesStrategy::execute(const float delta, TIEntity& tientity) {
    MovesComponent& movesComponent = MovesComponentSystem::Instance()->addComponent(tientity);
    PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);
    PathsComponent& pathsComponent = PathsComponentSystem::Instance()->addComponent(tientity);

    if (pathsComponent.hasPath()) {
        MovesComponentSystem::Instance()->setTargetRotation(movesComponent, positionComponent, tientity);

        this->accelerate(delta, movesComponent, pathsComponent, positionComponent);
        this->rotate(delta, movesComponent, positionComponent);
        return this->move(delta, movesComponent, pathsComponent, positionComponent);
    } else {
        return false;
    }
}


void SnapTurnMovesStrategy::rotate(const float delta, MovesComponent& movesComponent, PositionComponent& positionComponent) {
    positionComponent.rotation = movesComponent.targetRotation;
}
