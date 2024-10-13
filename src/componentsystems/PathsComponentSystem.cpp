#include "componentsystems/PathsComponentSystem.h" 

using namespace TIE;

PathsComponentSystem::PathsComponentSystem() {
	this->setName(PathsComponentSystem::PATHS);
}


void PathsComponentSystem::update(const float delta) {
	for (auto& c : this->components) {
		c.pathsComponent.pathStrategy->execute(delta, c.tientity);
	}
}


PathsComponent& PathsComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<PathsComponent>()) {
        PathsComponent& pathsComponent = tientity.addComponent<PathsComponent>();
        this->components.push_back({ 
			pathsComponent,
			tientity,
		});
        return pathsComponent;
	} else {
		return *tientity.getComponent<PathsComponent>();
	}
}


PathsComponent& PathsComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
    PathsComponent& component = this->addComponent(tientity);
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
