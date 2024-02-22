#include "managers/SceneManager.h"

#include <functional>
#include <memory>

#include "managers/ComponentSystemsManager.h"
#include "managers/ViewManager.h"
#include "managers/UIManager.h"
#include "objects/components/ShapeComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/factories/tientities/SceneLayerFactory.h"
#include "objects/tientities/common/SceneLayer.h"

using namespace TIE;

void SceneManager::initialize() {
	this->sceneGraphRoot = make_unique<SceneLayer>();
	this->sceneGraphRoot->setViewId(ViewManager::Instance()->getEngineViewId());
	this->sceneGraphRoot->setName("SceneGraphRoot");

	this->clientLayer = &SceneLayerFactory()
		.setParent(this->getSceneGraphRoot())
		.setViewId(ViewManager::Instance()->getClientViewId())
		.setName("ClientLayer")
	.build();

	this->engineLayer = &SceneLayerFactory()
		.setParent(this->getSceneGraphRoot())
		.setViewId(ViewManager::Instance()->getEngineViewId())
		.setName("EngineLayer")
	.build();
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


void SceneManager::updateGameState(const float delta) {
	if (!this->isSimulationPaused()) {
		ComponentSystemsManager::Instance()->updateComponentSystems(delta);
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
				ComponentSystemsManager::Instance()->removeComponents(**child);
			}
		}
		children.erase(std::remove_if(children.begin(), children.end(), std::mem_fn(&TIEntity::getRemove)), children.end());
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


const bool SceneManager::isSimulationPaused() {
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
