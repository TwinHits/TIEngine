#include "managers/ViewManager.h"

#include "objects/SceneLayer.h"

using namespace TIE;

SceneLayer::Layer SceneLayer::getLayer() {
	return this->layer;
}


void SceneLayer::setLayer(Layer layer) {
	this->layer = layer;
}


void SceneLayer::setViewId(GlobalId id) {
	this->viewId = id;
}


GlobalId SceneLayer::getViewId() {
	return this->viewId;
}
