#include "componentsystems/PathsComponentSystem.h" 

#include "componentsystems/GridComponentSystem.h"
#include "componentsystems/PathsComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/WireframeComponentSystem.h"
#include "managers/ComponentSystemsManager.h"
#include "managers/ScriptManager.h"
#include "managers/WorldManager.h"
#include "componentsystems/strategies/paths/GoToPathsStrategy.h"
#include "componentsystems/strategies/paths/ForwardPathsStrategy.h"
#include "utils/TIEMath.h"

using namespace TIE;

PathsComponentSystem::PathsComponentSystem() {
	this->setName(PathsComponentSystem::PATHS);

	initializePathStrategies();

	ComponentSystemsManager::Instance()->registerComponentPropertyKey(PathsComponentSystem::AT_DESTINATION, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(PathsComponentSystem::DESTINATION, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(PathsComponentSystem::DESTINATION_PATH, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(PathsComponentSystem::DESTINATION_X, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(PathsComponentSystem::DESTINATION_Y, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(PathsComponentSystem::STRATEGY, this);
}


void PathsComponentSystem::update(const float delta) {
	for (auto& c : this->components) {
		this->pathStrategies[c.pathsComponent.getPathStrategy()]->execute(delta, c.tientity);
	}
}


PathsComponent& PathsComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<PathsComponent>()) {
        PathsComponent& pathsComponent = tientity.addComponent<PathsComponent>();
        PositionComponent& positionComponent = tientity.addComponent<PositionComponent>();
        this->components.push_back({ 
			pathsComponent,
			positionComponent,
			tientity,
		});
        return pathsComponent;
	} else {
		return *tientity.getComponent<PathsComponent>();
	}
}


PathsComponent& PathsComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
    PathsComponent& component = this->addComponent(tientity);
	PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);
	const ScriptTableReader& reader = factory.getReader().getReader(PathsComponentSystem::PATHS);

	const std::string& strategyName = reader.get<std::string>(PathsComponentSystem::STRATEGY, GoToPathsStrategy::NAME);
	if (this->pathStrategiesByName.count(strategyName)) {
		component.setPathStrategy(this->pathStrategiesByName[strategyName]);
	}

	if (reader.hasKey(PathsComponentSystem::DESTINATION)) {
		const ScriptTableReader& destinationReader = reader.getReader(PathsComponentSystem::DESTINATION);
		float destinationX = destinationReader.get<float>(PathsComponentSystem::DESTINATION_X, 0);
		float destinationY = destinationReader.get<float>(PathsComponentSystem::DESTINATION_Y, 0);
		if (!destinationX) {
			destinationX = positionComponent.position.x;
		}
		if (!destinationY) {
			destinationY = positionComponent.position.y;
		}
	}

	return component;
}


bool PathsComponentSystem::removeComponent(TIEntity& tientity) {
	PathsComponent* pathsComponent = tientity.getComponent<PathsComponent>();
	if (pathsComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->pathsComponent == pathsComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<PathsComponent>();
	} else {
		return false;
	}
}


void PathsComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity)  {
    PathsComponent& pathsComponent = this->addComponent(tientity);
    if (key == PathsComponentSystem::DESTINATION) {
		pathsComponent.setDestinationDistance(value);
    } else if (key == PathsComponentSystem::DESTINATION_X) {
		pathsComponent.setDestination(sf::Vector2f(value, pathsComponent.getDestinaton().y));
	} else if (key == PathsComponentSystem::DESTINATION_Y) {
		pathsComponent.setDestination(sf::Vector2f(pathsComponent.getDestinaton().x, value));
	}
}


void PathsComponentSystem::setComponentProperty(const std::string& key, const sf::Vector2f& value, TIEntity& tientity)  {
	PathsComponent& pathsComponent = this->addComponent(tientity);
    if (key == PathsComponentSystem::DESTINATION) {
		pathsComponent.setDestination(value);
    }
}


void PathsComponentSystem::setComponentProperty(const std::string& key, const std::vector<sf::Vector2f>& value, TIEntity& tientity) {
	PathsComponent& pathsComponent = this->addComponent(tientity);
    if (key == PathsComponentSystem::DESTINATION_PATH) {
		pathsComponent.setPath(value);
    }
}


void PathsComponentSystem::setComponentProperty(const std::string& key, const sf::Vector2i& value, TIEntity& tientity) {
	PathsComponent& pathsComponent = this->addComponent(tientity);
    if (key == PathsComponentSystem::DESTINATION) {
		pathsComponent.setDestination(value);
    }
}


sol::object PathsComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
	PathsComponent* component = tientity.getComponent<PathsComponent>();
	if (component != nullptr) {
		if (key == PathsComponentSystem::AT_DESTINATION) {
			return ScriptManager::Instance()->getObjectFromValue(!component->hasPath());
		} else if (key == PathsComponentSystem::DESTINATION) {
			if (component->peekNextPathPosition()) {
				return ScriptManager::Instance()->getObjectFromValue(*component->peekNextPathPosition());
			}
		}
	}
	return ScriptManager::Instance()->getObjectFromValue(nullptr);
}


std::pair<GlobalId, GlobalId> PathsComponentSystem::addWireframe(TIEntity& tientity) {
	PathsComponent& pathsComponent = this->addComponent(tientity);
	PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);

	const sf::Vector2f origin = sf::Vector2f(0, 0);
	float distanceToTargetPosition = 0;
    sf::FloatRect bounds = sf::FloatRect(0, 0, 0, 0);
    float angleToTargetPosition = 0;
    if (pathsComponent.hasPath()) {
        const sf::Vector2f& targetPosition = *pathsComponent.peekNextPathPosition();
		distanceToTargetPosition = Math::distanceBetweenTwoPoints(positionComponent.worldPosition, targetPosition);
		bounds = sf::FloatRect(0, 0, distanceToTargetPosition, 0);
        angleToTargetPosition = Math::angleBetweenTwoPoints(positionComponent.worldPosition, targetPosition);
	}
	return WireframeComponentSystem::Instance()->createWireframe(tientity, bounds, origin, angleToTargetPosition);
}
 

void PathsComponentSystem::initializePathStrategies() {
	this->pathStrategies[PathStrategies::GOTO] = std::make_unique<GoToPathsStrategy>();
	this->pathStrategies[PathStrategies::FORWARD] = std::make_unique<ForwardPathsStrategy>();

	this->pathStrategiesByName = std::map<std::string, PathStrategies>({
		{ GoToPathsStrategy::NAME, PathStrategies::GOTO },
		{ ForwardPathsStrategy::NAME, PathStrategies::FORWARD },
	});
}
