#include "managers/ViewManager.h"

#include "objects/SceneLayer.h"

using namespace TIE;

SceneLayer::SceneLayer() {
	this->setDrawn(true);
	this->setType("Layer");
}


SceneLayer::~SceneLayer() {

}


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


void SceneLayer::draw(sf::RenderTarget& window, sf::RenderStates states) const {
	if (this->getDrawn()) {
		this->drawSelf(window, states);
		for (auto& child : this->getChildren()) {
			child->draw(window, states);	
		}
	}
}


void SceneLayer::drawSelf(sf::RenderTarget&, sf::RenderStates) const {
	ViewManager::Instance()->setActiveView(viewId);
}


void SceneLayer::updateSelf(const float delta) {
	
}
