#include "managers/UIManager.h"

#include "managers/SceneManager.h"
#include "objects/tientities/engine/DegreeGuide.h"
#include "objects/tientities/engine/MousePtrCoords.h"
#include "objects/tientities/engine/PerformanceDisplay.h"
#include "objects/tientities/engine/explorer/TIEntityExplorer.h"

using namespace TIE;

void UIManager::initialize() {
	SceneLayer& engineLayer = SceneManager::Instance()->getEngineLayer();
	std::unique_ptr<DegreeGuide> degreeGuide = make_unique<DegreeGuide>();
	engineLayer.attachChild(std::move(degreeGuide));

	std::unique_ptr<MousePtrCoords> mousePtrCoords = make_unique<MousePtrCoords>();
	engineLayer.attachChild(std::move(mousePtrCoords));
	
	std::unique_ptr<PerformanceDisplay> performanceDisplay = make_unique<PerformanceDisplay>();
	engineLayer.attachChild(std::move(performanceDisplay));

	std::unique_ptr<TIEntityExplorer> tientityExplorer = make_unique<TIEntityExplorer>();
	engineLayer.attachChild(std::move(tientityExplorer));
}


void UIManager::updateEngineEntities(const float delta) {
	return this->updateEngineEntities(SceneManager::Instance()->getEngineLayer(), delta);
}


void UIManager::updateEngineEntities(TIEntity& tientity, const float delta) {
	tientity.update(delta);
	if (tientity.hasChildren()) {
		for (auto& child : tientity.getChildren()) {
			this->updateEngineEntities(*child, delta);
		}
	}
}
