#include "managers/SceneManager.h"

#include <functional>

#include "componentsystems/AnimatedComponentSystem.h"
#include "componentsystems/BehaviorComponentSystem.h"
#include "componentsystems/CollidesComponentSystem.h"
#include "componentsystems/EventsComponentSystem.h"
#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/SpriteComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"
#include "managers/LogManager.h" 
#include "managers/TimeManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"
#include "managers/WorldManager.h"
#include "objects/SceneLayer.h"
#include "objects/components/ShapeComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/entities/DegreeGuide.h"
#include "objects/entities/MousePtrCoords.h"
#include "objects/entities/PerformanceDisplay.h"
#include "templates/MakeUnique.h"

using namespace TIE;

SceneManager::SceneManager() : clock(TimeManager::Instance()->addClock()) {}

bool SceneManager::initialize() {
	this->sceneGraphRoot = make_unique<SceneLayer>();
	this->sceneGraphRoot->setLayer(SceneLayer::Layer::ROOT);
	this->sceneGraphRoot->setViewId(ViewManager::Instance()->getEngineViewId());
	this->sceneGraphRoot->setName("SceneGraphRoot");

	this->clientLayer = &dynamic_cast<SceneLayer&>(this->sceneGraphRoot->attachChild(make_unique<SceneLayer>()));
	this->clientLayer->setLayer(SceneLayer::Layer::CLIENT);
	this->clientLayer->setViewId(ViewManager::Instance()->getClientViewId());
	this->clientLayer->setName("ClientLayer");

	this->engineLayer = &dynamic_cast<SceneLayer&>(this->sceneGraphRoot->attachChild(make_unique<SceneLayer>()));
	this->engineLayer->setLayer(SceneLayer::Layer::ENGINE);
	this->engineLayer->setViewId(ViewManager::Instance()->getEngineViewId());
	this->engineLayer->setName("EngineLayer");

	std::unique_ptr<DegreeGuide> degreeGuide = make_unique<DegreeGuide>();
	degreeGuide->initialize();
	this->engineLayer->attachChild(std::move(degreeGuide));

	std::unique_ptr<MousePtrCoords> mousePtrCoords = make_unique<MousePtrCoords>();
	mousePtrCoords->initialize();
	this->engineLayer->attachChild(std::move(mousePtrCoords));
	
	std::unique_ptr<PerformanceDisplay> performanceDisplay = make_unique<PerformanceDisplay>();
	performanceDisplay->initialize();
	this->engineLayer->attachChild(std::move(performanceDisplay));

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


/* //Investigate with collides component
TIEntity* SceneManager::findTIEntity(sf::Vector2f point) {
	return this->getClientLayer().findNode(point);	
}
*/


void SceneManager::updateGameState() {
	this->delta = this->clock.restart().asSeconds();

	WorldManager::Instance()->attachNewTIEntities();

	SpriteComponentSystem::Instance()->update(this->delta);
	TextComponentSystem::Instance()->update(this->delta);
	AnimatedComponentSystem::Instance()->update(this->delta);
	MovesComponentSystem::Instance()->update(this->delta);
	CollidesComponentSystem::Instance()->update(this->delta);
	EventsComponentSystem::Instance()->update(this->delta);
	BehaviorComponentSystem::Instance()->update(this->delta);

	this->updateEngineEntity(*(this->engineLayer));

	ViewManager::Instance()->updateCamera(this->delta);

	this->fps = this->calculateRollingAverageFPS(this->delta);
}


void SceneManager::removeTIEntities(std::vector<std::unique_ptr<TIEntity> >& entities) {
	entities.erase(std::remove_if(entities.begin(), entities.end(), std::mem_fn(&TIEntity::getRemove)), entities.end());
}


void SceneManager::updateEngineEntity(TIEntity& tientity) {

	tientity.update(this->delta);
	if (tientity.getChildren().size() > 0) {
		this->removeTIEntities(tientity.getChildren());
		for (auto& child : tientity.getChildren()) {
			this->updateEngineEntity(*child);
		}
	}
}


void SceneManager::render() {		

	window.clear();

	sf::RenderStates states;

	ViewManager::Instance()->setActiveView(this->clientLayer->getViewId());
	this->render(*(this->clientLayer), this->window, states);

	ViewManager::Instance()->setActiveView(this->engineLayer->getViewId());
	this->render(*(this->engineLayer), this->window, states);

	window.display();
}


float SceneManager::getFPS() {
	return this->fps;
}


float SceneManager::calculateRollingAverageFPS(const float delta) {
	static int index=0;
	static float sum=0;
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
	
	//Continue traversal if there's no graphics components, or if either component is drawn
	bool continueTraversal = textComponent == nullptr && spriteComponent == nullptr && shapeComponent == nullptr;
	if (spriteComponent != nullptr && spriteComponent->isDrawn()) {
		//states.transform *= spriteComponent->getTransform();
		window.draw(*dynamic_cast<sf::Sprite*>(spriteComponent), states);
		continueTraversal = true;
	}

	if (textComponent != nullptr && textComponent->isDrawn()) {
		window.draw(*dynamic_cast<sf::Text*>(textComponent));
		continueTraversal = true;
	}

	if (shapeComponent != nullptr && shapeComponent->isDrawn()) {
		window.draw(*dynamic_cast<sf::Shape*>(shapeComponent));
		continueTraversal = true;
	}

	if (continueTraversal) {
		for (auto& child : entity.getChildren()) {
			this->render(*child, window, states);
		}
	}
}
