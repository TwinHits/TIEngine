#include "componentsystems/strategies/paths/ForwardPathsStrategy.h"

#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/PathsComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "utils/TIEMath.h"

using namespace TIE;

bool ForwardPathsStrategy::execute(const float delta, TIEntity& tientity) {
    MovesComponent& movesComponent = MovesComponentSystem::Instance()->addComponent(tientity);
    PathsComponent& pathsComponent = PathsComponentSystem::Instance()->addComponent(tientity);
    PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);

    sf::Vector2f velocity = sf::Vector2f(movesComponent.targetSpeed * 2, positionComponent.rotation);
    sf::Vector2f distance = Math::translateVelocityByTime(velocity,  1);
    sf::Vector2f destination = sf::Vector2f(positionComponent.position.x + distance.x, positionComponent.position.y + distance.y);

    pathsComponent.setSinglePositionPath(destination);

    return true;
}
