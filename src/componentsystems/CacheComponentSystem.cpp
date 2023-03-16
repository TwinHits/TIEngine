#include "componentsystems/CacheComponentSystem.h"

#include <sol/sol.hpp>

#include "objects/tientities/TIEntity.h"
#include "objects/components/CacheComponent.h"
#include "managers/ScriptManager.h"
#include "utils/StringHelpers.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

CacheComponentSystem::CacheComponentSystem() {
    this->setName(CacheComponentSystem::CACHE);
    ComponentSystems::insertComponentPropertyIntoMap(CacheComponentSystem::CACHE, this->componentPropertyMap);
}


void CacheComponentSystem::update(const float delta) {}


CacheComponent& CacheComponentSystem::addComponent(TIEntity& tientity) {
    if (!tientity.hasComponent<CacheComponent>()) {
        CacheComponent& cacheComponent = tientity.addComponent<CacheComponent>();
        cacheComponent.setCache(ScriptManager::Instance()->getNewTable());
        this->components.push_back({ cacheComponent });
        return cacheComponent;
    } else {
        return *tientity.getComponent<CacheComponent>();
    }
}


CacheComponent& CacheComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
    CacheComponent& cacheComponent = this->addComponent(tientity);
    sol::table copy = ScriptManager::Instance()->copyTable(factory.tableValues.at("cache"));
    cacheComponent.setCache(copy);
    return cacheComponent;
}


bool CacheComponentSystem::removeComponent(TIEntity& tientity) {
    CacheComponent* cacheComponent = tientity.getComponent<CacheComponent>();
    if (cacheComponent != nullptr) {
        for (auto i = this->components.begin(); i != this->components.end(); ++i) {
            if (&i->cacheComponent == cacheComponent) {
                this->components.erase(i);
                break;
            }
        }
        return tientity.removeComponent<CacheComponent>();
    } else {
        return false;
    }
}


bool CacheComponentSystem::setComponentProperty(const std::string& key, bool value, TIEntity& tientity) {
    return false;
}


bool CacheComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity)  {
    return false;
}


bool CacheComponentSystem::setComponentProperty(const std::string& key, const std::string& value, TIEntity& tientity)  {
    return false;
}


sol::object CacheComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
    return ScriptManager::Instance()->getObjectFromValue(nullptr);
}


void CacheComponentSystem::updateCache(TIEntity& tientity, sol::table& cache) {
    CacheComponent* cacheComponent = tientity.getComponent<CacheComponent>();
    if (cacheComponent != nullptr) {
        cacheComponent->setCache(cache);
    } else {
        this->addComponent(tientity).setCache(cache);
    }
}


sol::table& CacheComponentSystem::getCache(TIEntity& tientity) {
    CacheComponent* cacheComponent = tientity.getComponent<CacheComponent>();
    if (cacheComponent != nullptr) {
        return cacheComponent->getCache();
    } else {
        return this->addComponent(tientity).getCache();
    }
}
