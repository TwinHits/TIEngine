#include "componentsystems/strategies/paths/GoToPathsStrategy.h"

#include "componentsystems/PathsComponentSystem.h"

using namespace TIE;

 bool GoToPathsStrategy::execute(const float delta, TIEntity& tientity) { 
    PathsComponent& pathsComponent = PathsComponentSystem::Instance()->addComponent(tientity);

    if (pathsComponent.isHasDestinationChanged()) {
        pathsComponent.setSinglePositionPath(pathsComponent.getDestinaton());
        pathsComponent.setHasDestinationChanged(false);
    }

    return false;
}
