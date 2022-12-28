#include "managers/SceneManager.h"

#include <functional>
#include <memory>
#include <vector>

#include "componentsystems/AnimatedComponentSystem.h"
#include "componentsystems/CollidesComponentSystem.h"
#include "componentsystems/ComponentSystem.h"
#include "componentsystems/CacheComponentSystem.h"
#include "componentsystems/EventsComponentSystem.h"
#include "componentsystems/GridComponentSystem.h"
#include "componentsystems/LifecycleComponentSystem.h"
#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/ShapeComponentSystem.h"
#include "componentsystems/SpriteComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "managers/ScriptManager.h"
#include "managers/TimeManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"
#include "objects/SceneLayer.h"
#include "objects/components/ShapeComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/entities/ComponentPropertiesDisplay.h"
#include "objects/entities/DegreeGuide.h"
#include "objects/entities/MousePtrCoords.h"
#include "objects/entities/PerformanceDisplay.h"
#include "objects/factories/SceneLayerFactory.h"
#include "templates/MakeUnique.h"

using namespace TIE;

bool SceneManager::initialize() {
	this->sceneGraphRoot = make_unique<SceneLayer>();
	this->sceneGraphRoot->setLayer(SceneLayer::Layer::ROOT);
	this->sceneGraphRoot->setViewId(ViewManager::Instance()->getEngineViewId());
	this->sceneGraphRoot->setName("SceneGraphRoot");

	this->clientLayer = &SceneLayerFactory().setParent(this->getSceneGraphRoot()).setViewId(ViewManager::Instance()->getClientViewId()).setName("ClientLayer").setLayer(SceneLayer::Layer::CLIENT).build();
	this->engineLayer = &SceneLayerFactory().setParent(this->getSceneGraphRoot()).setViewId(ViewManager::Instance()->getEngineViewId()).setName("EngineLayer").setLayer(SceneLayer::Layer::ENGINE).build();

	std::unique_ptr<DegreeGuide> degreeGuide = make_unique<DegreeGuide>();
	degreeGuide->initialize();
	this->engineLayer->attachChild(std::move(degreeGuide));

	std::unique_ptr<MousePtrCoords> mousePtrCoords = make_unique<MousePtrCoords>();
	mousePtrCoords->initialize();
	this->engineLayer->attachChild(std::move(mousePtrCoords));
	
	std::unique_ptr<PerformanceDisplay> performanceDisplay = make_unique<PerformanceDisplay>();
	performanceDisplay->initialize();
	this->engineLayer->attachChild(std::move(performanceDisplay));

	std::unique_ptr<ComponentPropertiesDisplay> componentPropertiesDisplay = make_unique<ComponentPropertiesDisplay>();
	this->engineLayer->attachChild(std::move(componentPropertiesDisplay));

	// Component System registration, order of initialization, and order of update
	// Update data operations
	this->componentSystems.push_back(EventsComponentSystem::Instance());
	this->componentSystems.push_back(LifecycleComponentSystem::Instance());
	this->componentSystems.push_back(CacheComponentSystem::Instance());

	// Update Position Operations
	this->componentSystems.push_back(PositionComponentSystem::Instance());
	this->componentSystems.push_back(MovesComponentSystem::Instance());

	// Drawing operations
	this->componentSystems.push_back(SpriteComponentSystem::Instance());
	this->componentSystems.push_back(AnimatedComponentSystem::Instance());
	this->componentSystems.push_back(TextComponentSystem::Instance());
	this->componentSystems.push_back(ShapeComponentSystem::Instance());

	// Other Operations
	this->componentSystems.push_back(GridComponentSystem::Instance());
	this->componentSystems.push_back(CollidesComponentSystem::Instance());

	//this->componentSystemPropertiesMap = ScriptManager::Instance()->getNewTable();
	for (ComponentSystem* componentSystem : SceneManager::Instance()->getComponentSystems()) {
		// List of valid component names
		this->componentNamesToComponentSystems[componentSystem->getName()] = componentSystem;
		// Assemble component system properties map
		this->componentSystemPropertiesMap = componentSystem->populateComponentSystemsPropertiesMap(this->componentSystemPropertiesMap);
	}

	return true;
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
    for (ComponentSystem* componentSystem : this->componentSystems) {
        componentSystem->update(delta);
    }
    this->updateEngineEntities(*(this->engineLayer), delta);

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


void SceneManager::updateEngineEntities(TIEntity& tientity, const float delta) {

	tientity.update(delta);
	if (tientity.getChildren().size() > 0) {
		for (auto& child : tientity.getChildren()) {
			this->updateEngineEntities(*child, delta);
		}
	}
}


void SceneManager::render() {		
	window.clear();
	sf::RenderStates states;
	this->render(*(this->sceneGraphRoot), this->window, states);
	window.display();
}


float SceneManager::getFPS() {
	return this->fps;
}


void SceneManager::setTIEntitiesMarkedForRemove(bool flag) {
	this->tientitiesMarkedForRemove = flag;
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
		for (auto& shape : shapeComponent->getShapes()) {
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
