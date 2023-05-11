#include "managers/SceneManager.h"

#include <functional>
#include <memory>
#include <vector>

#include "componentsystems/AnimatedComponentSystem.h"
#include "componentsystems/BehavesComponentSystem.h"
#include "componentsystems/CollidesComponentSystem.h"
#include "componentsystems/ComponentSystem.h"
#include "componentsystems/CacheComponentSystem.h"
#include "componentsystems/EventsComponentSystem.h"
#include "componentsystems/GridComponentSystem.h"
#include "componentsystems/LifecycleComponentSystem.h"
#include "componentsystems/LineComponentSystem.h"
#include "componentsystems/MessagesComponentSystem.h"
#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/ShapeComponentSystem.h"
#include "componentsystems/SpriteComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/WireframeComponentSystem.h"
#include "managers/ViewManager.h"
#include "managers/UIManager.h"
#include "objects/tientities/SceneLayer.h"
#include "objects/components/ShapeComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/factories/SceneLayerFactory.h"

using namespace TIE;

void SceneManager::initialize() {
	this->sceneGraphRoot = make_unique<SceneLayer>();
	this->sceneGraphRoot->setLayer(SceneLayer::Layer::ROOT);
	this->sceneGraphRoot->setViewId(ViewManager::Instance()->getEngineViewId());
	this->sceneGraphRoot->setName("SceneGraphRoot");

	this->clientLayer = &SceneLayerFactory().setParent(this->getSceneGraphRoot()).setViewId(ViewManager::Instance()->getClientViewId()).setName("ClientLayer").setLayer(SceneLayer::Layer::CLIENT).build();
	this->engineLayer = &SceneLayerFactory().setParent(this->getSceneGraphRoot()).setViewId(ViewManager::Instance()->getEngineViewId()).setName("EngineLayer").setLayer(SceneLayer::Layer::ENGINE).build();

	// Component System registration, order of initialization, and order of update
	// Update data operations
	this->componentSystems.push_back(CacheComponentSystem::Instance());
	this->componentSystems.push_back(MessagesComponentSystem::Instance());
	this->componentSystems.push_back(EventsComponentSystem::Instance());
	this->componentSystems.push_back(LifecycleComponentSystem::Instance());
	this->componentSystems.push_back(BehavesComponentSystem::Instance());

	// Update Position Operations
	this->componentSystems.push_back(PositionComponentSystem::Instance());
	this->componentSystems.push_back(MovesComponentSystem::Instance());

	// Other Operations
	this->componentSystems.push_back(GridComponentSystem::Instance());
	this->componentSystems.push_back(CollidesComponentSystem::Instance());

	// Drawing operations
	this->componentSystems.push_back(SpriteComponentSystem::Instance());
	this->componentSystems.push_back(AnimatedComponentSystem::Instance());
	this->componentSystems.push_back(TextComponentSystem::Instance());
	this->componentSystems.push_back(ShapeComponentSystem::Instance());
	this->componentSystems.push_back(LineComponentSystem::Instance());
	this->componentSystems.push_back(WireframeComponentSystem::Instance());

	for (ComponentSystem* componentSystem : SceneManager::Instance()->getComponentSystems()) {
		// List of valid component names
		this->componentNamesToComponentSystems[componentSystem->getName()] = componentSystem;
		// Assemble component system properties map
		this->componentSystemPropertiesMap = componentSystem->populateComponentSystemsPropertiesMap(this->componentSystemPropertiesMap);
	}
}


SceneLayer& SceneManager::getSceneGraphRoot() {
	return *this->sceneGraphRoot;
}


SceneLayer& SceneManager::getEngineLayer() {
	return *this->engineLayer;
}


SceneLayer& SceneManager::getClientLayer() {
	return *this->clientLayer;
}


const std::vector<ComponentSystem*>& SceneManager::getComponentSystems() {
	return this->componentSystems;
}


bool SceneManager::isValidComponentName(const std::string& componentName) {
	return this->componentNamesToComponentSystems.count(componentName);
}


ComponentSystem* SceneManager::getComponentSystemByComponentName(const std::string& componentName) {
	if (this->isValidComponentName(componentName)) {
		return this->componentNamesToComponentSystems.at(componentName);
	} else {
		return nullptr;
	}
}


const ComponentSystems::ComponentSystemPropertiesMap& SceneManager::getComponentSystemPropertiesMap() {
	return this->componentSystemPropertiesMap;
}


void SceneManager::updateGameState(const float delta) {
	if (!this->simulationPaused) {
		for (ComponentSystem* componentSystem : this->componentSystems) {
			componentSystem->update(delta);
		}
	}
    UIManager::Instance()->updateEngineEntities(delta);

    if (this->tientitiesMarkedForRemove) {
        this->removeTIEntities(*this->sceneGraphRoot);
    }

    //Update Camera and FPS
    ViewManager::Instance()->updateCamera(delta);
    this->fps = this->calculateRollingAverageFPS(delta);
}


void SceneManager::removeTIEntities(TIEntity& tientity) {
	auto& children = tientity.getChildren();
	if (children.size() > 0) {
		for (auto child = children.begin(); child != children.end(); ++child) {
			this->removeTIEntities(**child);
			if ((*child)->getRemove()) {
				this->removeComponents(**child);
			}
		}
		children.erase(std::remove_if(children.begin(), children.end(), std::mem_fn(&TIEntity::getRemove)), children.end());
	}
}


void SceneManager::removeComponents(TIEntity& tientity) {
	LifecycleComponentSystem::Instance()->runRemoved(tientity);
	for (ComponentSystem* componentSystem : this->componentSystems) {
		componentSystem->removeComponent(tientity);
	}
}


void SceneManager::render() {		
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
	window.clear();
	sf::RenderStates states;
	this->render(*(this->sceneGraphRoot), window, states);
	window.display();
}


float SceneManager::getFPS() {
	return this->fps;
}


void SceneManager::setTIEntitiesMarkedForRemove(bool flag) {
	this->tientitiesMarkedForRemove = flag;
}


void SceneManager::setSimulationPaused(const bool simulationPaused) {
	this->simulationPaused = simulationPaused;
}


const bool SceneManager::getSimulationPaused() {
	return this->simulationPaused;
}


float SceneManager::calculateRollingAverageFPS(const float delta) {
	static int index = 0;
	static float sum = 0;
	static float ticks[100] = { 0 };

	float tick = 1 / delta;

	sum -= ticks[index];
	sum += tick;
	ticks[index] = tick;
	if (++index == 100) {
		index = 0;
	}

	return sum / 100;
}


void SceneManager::render(TIEntity& entity, sf::RenderWindow& window, sf::RenderStates states) {
	SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
	TextComponent* textComponent = entity.getComponent<TextComponent>();
	ShapeComponent* shapeComponent = entity.getComponent<ShapeComponent>();

	if (entity.isSceneLayer()) {
		SceneLayer* sceneLayer = dynamic_cast<SceneLayer*>(&entity);
		ViewManager::Instance()->setActiveView(sceneLayer->getViewId());
	}
	
	//Continue traversal if there's no graphics components, or if any graphics component is drawn
	bool continueTraversal = textComponent == nullptr && spriteComponent == nullptr && shapeComponent == nullptr;
	if (spriteComponent != nullptr && spriteComponent->isDrawn()) {
		window.draw(spriteComponent->getSprite(), states);
		continueTraversal = true;
	}

	if (textComponent != nullptr && textComponent->isDrawn()) {
		window.draw(textComponent->getText(), states);
		continueTraversal = true;
	}

	if (shapeComponent != nullptr && shapeComponent->isDrawn()) {
		for (auto& [id, shape] : shapeComponent->getShapes()) {
			window.draw(*shape, states);
		}
		continueTraversal = true;
	}

	if (continueTraversal) {
		for (auto& child : entity.getChildren()) {
			this->render(*child, window, states);
		}
	}
}
