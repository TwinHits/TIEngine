#include <SFML/Graphics.hpp>

#include "objects/components/WireframeComponent.h"

using namespace TIE;

void WireframeComponent::setShowWireframe(const bool showWireframe) {
    this->showWireframe = showWireframe;
}


const bool WireframeComponent::getShowWireframe() {
    return this->showWireframe;
}


void WireframeComponent::addWireframeShapeIds(const Component* component, std::pair<GlobalId, GlobalId> wireframeShapeIds) {
    this->componentToWireframeShapeIds[component] = wireframeShapeIds;
    
}


const std::pair<GlobalId, GlobalId>* WireframeComponent::getWireframeShapeIds(const Component* component) {
    if (this->componentToWireframeShapeIds.count(component)) {
        return &this->componentToWireframeShapeIds.at(component);
    } else {
        return nullptr;
    }
}