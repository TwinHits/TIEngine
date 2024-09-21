#include "objects/factories/tientities/TIEntityFactory.h"

#include <sol/sol.hpp>

#include "componentsystems/ComponentSystem.h"
#include "componentsystems/LifecycleComponentSystem.h"
#include "componentsystems/WireframeComponentSystem.h"
#include "managers/ComponentSystemsManager.h"
#include "managers/HashManager.h"
#include "managers/SceneManager.h"
#include "managers/ScriptManager.h"
#include "managers/WorldManager.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

TIEntityFactory::TIEntityFactory() {
	this->id = HashManager::Instance()->getNewGlobalId();
	this->reader = TIE::make_unique<ScriptTableReader>();
}


TIEntityFactory::TIEntityFactory(const sol::table& definition) {
	this->id = HashManager::Instance()->getNewGlobalId();
	this->reader = TIE::make_unique<ScriptTableReader>(definition);
}


TIEntity& TIEntityFactory::build() {
	return this->build(this->getReader());
}


TIEntity& TIEntityFactory::build(const ScriptTableReader& reader) {
	if (this->parent == nullptr) {
		this->setParent(&SceneManager::Instance()->getClientLayer());
	}
	TIEntity& tientity = this->parent->attachChild();

	const ScriptTableReader& metaReader = reader.getReader("tientity");
	tientity.setName(metaReader.get<std::string>(TIEntityFactory::NAME, this->name));
	this->setShowWireFrame(WireframeComponentSystem::Instance()->getShowWireframe(tientity.getParent()));

    for (ComponentSystem* componentSystem : ComponentSystemsManager::Instance()->getComponentSystems()) {
        if (reader.hasKey(componentSystem->getName())) {
            componentSystem->addComponent(*this, tientity);
        } else if (componentSystem->getName() == WireframeComponentSystem::WIREFRAME && this->getShowWireframe()) {
            componentSystem->addComponent(*this, tientity);
        }
    }

    WorldManager::Instance()->saveTIEntityFactory(tientity.getName(), *this);
	LifecycleComponentSystem::Instance()->runCreated(tientity);

	return tientity;
}


TIEntityFactory& TIEntityFactory::setParent(TIEntity* parent) {
	this->parent = parent;
	return *this;
}


TIEntity* TIEntityFactory::getParent() {
	return this->parent;
}


const GlobalId TIEntityFactory::getId() {
	return this->id;
}


const ScriptTableReader& TIEntityFactory::getReader() {
	return *this->reader;
}


const ScriptTableReader& TIEntityFactory::getReader() const {
	return *this->reader;
}


TIEntityFactory& TIEntityFactory::setName(std::string name) {
	this->name = name;
	return *this;
}


const std::string& TIEntityFactory::getName() {
	return this->name;
}


const bool TIEntityFactory::getShowWireframe() {
	return this->showWireframe;
}


const bool TIEntityFactory::getShowWireframe() const {
	return this->showWireframe;
}


void TIEntityFactory::setShowWireFrame(const bool showWireframe) {
	this->showWireframe = showWireframe;
}
