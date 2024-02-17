#include "objects/tientities/engine/explorer/TIEntityExplorer.h"

#include <memory>

#include "objects/tientities/engine/explorer/ComponentPropertiesDisplay.h"
#include "templates/MakeUnique.h"
#include "managers/MessageManager.h"
#include "managers/ViewManager.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

TIEntityExplorer::TIEntityExplorer() {
    this->setName("TIEntity Explorer");
    this->setViewId(ViewManager::Instance()->getEngineViewId());

    std::unique_ptr<ComponentPropertiesDisplay> componentPropertiesDisplay = make_unique<ComponentPropertiesDisplay>();
    this->attachChild(std::move(componentPropertiesDisplay));

    MessageManager::Instance()->subscribe("END", std::bind(&TIEntityExplorer::onShowHide, this));
}


void TIEntityExplorer::onShowHide() {
    for (auto& child : this->getChildren()) {
        ComponentSystems::setDrawn(*child, !ComponentSystems::isDrawn(*child));
    }
}
