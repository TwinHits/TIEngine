#include "objects/SceneLayer.h"

using namespace TIE;

SceneLayer::SceneLayer() {

}


SceneLayer::~SceneLayer() {

}


SceneLayer::Layer SceneLayer::getLayer() {
	return this->layer;
}


void SceneLayer::setLayer(Layer layer) {
	this->layer = layer;
}


void SceneLayer::drawSelf(sf::RenderWindow&, sf::RenderStates) const {

}


void SceneLayer::updateSelf(const float delta) {
	
}
