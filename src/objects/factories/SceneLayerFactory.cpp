#include "objects/factories/tientities/SceneLayerFactory.h"

#include "managers/SceneManager.h"
#include "objects/tientities/common/SceneLayer.h"

using namespace TIE;

SceneLayerFactory::SceneLayerFactory() {
    this->parent = &SceneManager::Instance()->getClientLayer();
}


SceneLayer& SceneLayerFactory::build() {
    SceneLayer& sceneLayer = dynamic_cast<SceneLayer&>(this->parent->attachChild(make_unique<SceneLayer>()));
    sceneLayer.setViewId(this->viewId);
    sceneLayer.setName(this->name);
    return sceneLayer;
}


SceneLayerFactory& SceneLayerFactory::setName(const std::string& name) {
    this->name = name;
    return *this;
}


SceneLayerFactory& SceneLayerFactory::setParent(TIEntity& parent) {
    this->parent = &parent;
    return *this;
}


SceneLayerFactory& SceneLayerFactory::setViewId(GlobalId viewId) {
    this->viewId = viewId;
    return *this;
}
