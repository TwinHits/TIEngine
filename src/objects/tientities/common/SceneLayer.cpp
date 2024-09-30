#include "objects/tientities/common/SceneLayer.h"

using namespace TIE;

void SceneLayer::setViewId(GlobalId id) {
	this->viewId = id;
}


GlobalId SceneLayer::getViewId() {
	return this->viewId;
}


bool SceneLayer::isSceneLayer() {
	return true;
}
