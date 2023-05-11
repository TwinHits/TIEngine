#include "managers/UIManager.h"

#include "managers/SceneManager.h"
#include "objects/tientities/ComponentPropertiesDisplay.h"
#include "objects/tientities/DegreeGuide.h"
#include "objects/tientities/MousePtrCoords.h"
#include "objects/tientities/PerformanceDisplay.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

bool UIManager::initialize() {
	SceneLayer& engineLayer = SceneManager::Instance()->getEngineLayer();
	std::unique_ptr<DegreeGuide> degreeGuide = make_unique<DegreeGuide>();
	engineLayer.attachChild(std::move(degreeGuide));

	std::unique_ptr<MousePtrCoords> mousePtrCoords = make_unique<MousePtrCoords>();
	engineLayer.attachChild(std::move(mousePtrCoords));
	
	std::unique_ptr<PerformanceDisplay> performanceDisplay = make_unique<PerformanceDisplay>();
	engineLayer.attachChild(std::move(performanceDisplay));

	std::unique_ptr<ComponentPropertiesDisplay> componentPropertiesDisplay = make_unique<ComponentPropertiesDisplay>();
	engineLayer.attachChild(std::move(componentPropertiesDisplay));

	return true;
}


void UIManager::updateEngineEntities(const float delta) {
	return this->updateEngineEntities(SceneManager::Instance()->getEngineLayer(), delta);
}


void UIManager::updateEngineEntities(TIEntity& tientity, const float delta) {
	tientity.update(delta);
	if (tientity.getChildren().size() > 0) {
		for (auto& child : tientity.getChildren()) {
			this->updateEngineEntities(*child, delta);
		}
	}
}
