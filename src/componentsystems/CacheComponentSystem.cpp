#include "componentsystems/CacheComponentSystem.h"

#include <sol/sol.hpp>

#include <string>

#include "objects/tientities/TIEntity.h"
#include "objects/components/CacheComponent.h"
#include "managers/ComponentSystemsManager.h"
#include "managers/ScriptManager.h"
#include "utils/String.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

CacheComponentSystem::CacheComponentSystem() {
    this->setName(CacheComponentSystem::CACHE);
    ComponentSystemsManager::Instance()->registerComponentPropertyKey(CacheComponentSystem::CACHE, this);
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
    sol::table copy = ScriptManager::Instance()->copyTable(*factory.getReader().get<sol::table>(CacheComponentSystem::CACHE));
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


void CacheComponentSystem::setCacheValue(TIEntity& tientity, const std::string& key, const sol::object& value) {
    CacheComponent& cacheComponent = this->addComponent(tientity);
    sol::table& cache = cacheComponent.getCache();
    cache.traverse_set(key, value);
}


 sol::object CacheComponentSystem::getCacheValue(TIEntity& tientity, const std::string& key) {
    CacheComponent* cacheComponent = tientity.getComponent<CacheComponent>();
    if (cacheComponent != nullptr) {
        sol::table& cache = cacheComponent->getCache();
        return cache[key];
    } else {
        return sol::nil;
    }
}


 sol::object CacheComponentSystem::getCacheValueOr(TIEntity& tientity, const std::string& key, const sol::object& value) {
     CacheComponent& cacheComponent = this->addComponent(tientity);
     sol::table& cache = cacheComponent.getCache();
     if (!cache[key].valid()) {
        cache.traverse_set(key, value);
     }
     return cache[key];
 }
