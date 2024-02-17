#include "objects/tientities/engine/explorer/TIEntityExplorer.h"

#include <memory>

#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/SpriteComponentSystem.h"
#include "managers/AssetsManager.h"
#include "managers/MessageManager.h"
#include "managers/SceneManager.h"
#include "managers/ViewManager.h"
#include "objects/components/SpriteComponent.h"
#include "objects/constants/MessageSubscriptions.h"
#include "objects/tientities/engine/explorer/ComponentPropertiesDisplay.h"
#include "templates/MakeUnique.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

TIEntityExplorer::TIEntityExplorer() {
    this->setName("TIEntity Explorer");
    this->setViewId(ViewManager::Instance()->getEngineViewId());

    std::unique_ptr<ComponentPropertiesDisplay> componentPropertiesDisplay = make_unique<ComponentPropertiesDisplay>();
    this->attachChild(std::move(componentPropertiesDisplay));

    MessageManager::Instance()->subscribe("END", std::bind(&TIEntityExplorer::onToggleShowHide, this));
	MessageManager::Instance()->subscribe(MessageSubscriptions::WINDOW_SIZE_CHANGE, std::bind(&TIEntityExplorer::onWindowSizeChange, this));
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


void TIEntityExplorer::onToggleShowHide() {
    SceneManager::Instance()->setSimulationPaused(!SceneManager::Instance()->isSimulationPaused());
    ComponentSystems::setDrawn(*this, !ComponentSystems::isDrawn(*this));
    for (auto& child : this->getChildren()) {
        ComponentSystems::setDrawn(*child, !ComponentSystems::isDrawn(*child));
    }
}


void TIEntityExplorer::onWindowSizeChange() {
    const sf::Vector2i& windowSize = WindowManager::Instance()->getWindowSize();
    this->setBackgroundPosition(windowSize);
    this->setBackgroundSize(windowSize);
}
