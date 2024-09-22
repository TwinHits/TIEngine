#include "objects/tientities/engine/explorer/TIEntityExplorer.h"

#include <memory>

#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/SpriteComponentSystem.h"
#include "constants/MessageSubscriptions.h"
#include "managers/AssetsManager.h"
#include "managers/LogManager.h"
#include "managers/MessageManager.h"
#include "managers/SceneManager.h"
#include "managers/ViewManager.h"
#include "objects/components/SpriteComponent.h"
#include "objects/tientities/engine/explorer/BehaviorTreeDisplay.h"
#include "objects/tientities/engine/explorer/ComponentPropertiesDisplay.h"
#include "utils/ComponentSystems.h"
#include "objects/factories/tientities/SceneLayerFactory.h"
#include "objects/factories/ui/ButtonFactory.h"

using namespace TIE;

TIEntityExplorer::TIEntityExplorer() {
    this->setName("TIEntity Explorer");
    this->setViewId(ViewManager::Instance()->getEngineViewId());
    this->selectedTIEntity = &SceneManager::Instance()->getClientLayer();

    MessageManager::Instance()->subscribe("END", std::bind(&TIEntityExplorer::onToggleShowHide, this));
	MessageManager::Instance()->subscribe(MessageSubscriptions::WINDOW_SIZE_CHANGE, std::bind(&TIEntityExplorer::onWindowSizeChange, this));
}


void TIEntityExplorer::update(float delta) {}


void TIEntityExplorer::createButtons() {
    if (this->selectedTIEntity != nullptr && !this->selectedTIEntity->getChildren().empty()) {
        this->buttonSceneLayer->setRemoveChildren(true);
        this->buttonToChild.clear();

        const sf::Vector2i& windowSize = WindowManager::Instance()->getWindowSize();
        sf::Vector2f buttonSize = sf::Vector2f(200, 50);
        const float buttonPadding = (windowSize.y / this->selectedTIEntity->getChildren().size() - buttonSize.y) / 2;

        sf::Vector2f position = this->tientitiesDisplayPosition;
        for (auto& child : this->selectedTIEntity->getChildren()) {
            position += sf::Vector2f(0, buttonPadding);
            TIEntity& button = ButtonFactory()
                .setText(child->getName())
                .setOnClick(std::bind(&TIEntityExplorer::onButtonClick, this, std::placeholders::_1))
                .setPosition(position)
                .setSize(buttonSize)
                .setDrawn(this->show).setParent(this->buttonSceneLayer).build();

            this->buttonToChild.insert({ button.getId(), child.get()});
            position += sf::Vector2f(0, buttonSize.y);
            position += sf::Vector2f(0, buttonPadding);
        }
    }
}


void TIEntityExplorer::setBackgroundSize(const sf::Vector2i& windowSize) {
    SpriteComponent& spriteComponent = SpriteComponentSystem::Instance()->addComponent(*this);
    spriteComponent.setTexture(AssetsManager::Instance()->getTexture("dev_console.png"));
    sf::FloatRect& bounds = spriteComponent.getLocalBounds();
    float scaleX = float(windowSize.x) / float(bounds.width);
    float scaleY = float(windowSize.y) / float(bounds.height);
    const sf::Vector2f scale = sf::Vector2f(scaleX, scaleY);
    spriteComponent.setScale(scale);
    spriteComponent.setOrigin(0, 0);
    spriteComponent.setDrawn(false);
}


void TIEntityExplorer::setBackgroundPosition(const sf::Vector2i& windowSize) {
    PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(*this);
    positionComponent.position = sf::Vector2f(-windowSize.x / 2.0f, -windowSize.y / 2.0f);
}


void TIEntityExplorer::setAreaPositions(const sf::Vector2i& windowSize) {
    this->tientitiesDisplayPosition = sf::Vector2f(windowSize.x * 0.1f, 0);
    this->componentPropertiesDisplayPosition = sf::Vector2f(windowSize.x * 0.2f, 0);
    this->behaviorTreeDisplayPosition = sf::Vector2f(windowSize.x * 0.33f, 0);
}


void TIEntityExplorer::setComponentPropertiesDisplay() {
    std::unique_ptr<ComponentPropertiesDisplay> componentPropertiesDisplay = make_unique<ComponentPropertiesDisplay>();
    this->componentPropertiesDisplay = componentPropertiesDisplay.get();
    this->componentPropertiesDisplay->setTIEntity(this->selectedTIEntity);
    this->attachChild(std::move(componentPropertiesDisplay));
    PositionComponentSystem::Instance()->setPosition(*this->componentPropertiesDisplay, this->componentPropertiesDisplayPosition);
}


void TIEntityExplorer::setBehaviorTreeDisplay() {
    const sf::Vector2i& windowSize = WindowManager::Instance()->getWindowSize();
    sf::Vector2f behaviorTreeDisplaySize = sf::Vector2f(windowSize.x - this->behaviorTreeDisplayPosition.x, windowSize.y);
    std::unique_ptr<BehaviorTreeDisplay> behaviorTreeDisplay = make_unique<BehaviorTreeDisplay>(*this->selectedTIEntity, behaviorTreeDisplaySize);
    this->behaviorTreeDisplay = behaviorTreeDisplay.get();
    this->attachChild(std::move(behaviorTreeDisplay));
    PositionComponentSystem::Instance()->setPosition(*this->behaviorTreeDisplay, this->behaviorTreeDisplayPosition);
}


void TIEntityExplorer::onToggleShowHide() {
    this->show = !this->show;

    ComponentSystems::setDrawn(*this, this->show);
    if (this->show) {
        this->selectedTIEntity = &SceneManager::Instance()->getClientLayer();
        this->buttonSceneLayer = &SceneLayerFactory().setName("Button Scene Layer").setParent(*this).setViewId(this->getViewId()).build();

        this->createButtons();
        this->setComponentPropertiesDisplay();
        this->setBehaviorTreeDisplay();
        for (auto& child : this->getChildren()) {
            ComponentSystems::setDrawn(*child, this->show);
        }
    } else {
        this->setRemoveChildren(true);
    }
}


void TIEntityExplorer::onWindowSizeChange() {
    const sf::Vector2i& windowSize = WindowManager::Instance()->getWindowSize();
    this->setBackgroundPosition(windowSize);
    this->setBackgroundSize(windowSize);
    this->setAreaPositions(windowSize);
}


void TIEntityExplorer::onButtonClick(Message& message) {
    if (this->buttonToChild.count(message.senderId) && this->buttonToChild.at(message.senderId) != nullptr) {
        this->selectedTIEntity = this->buttonToChild.at(message.senderId);
        this->componentPropertiesDisplay->setTIEntity(this->selectedTIEntity);
        this->behaviorTreeDisplay->setTIEntity(*this->selectedTIEntity);
        this->createButtons();
    } else {
        LogManager::Instance()->error("TIEntityExplorer buttonToChild map does not have this message's sender id as a key.");
    }
}
