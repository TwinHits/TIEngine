#include "componentsystems/CacheComponentSystem.h"

#include <sol/sol.hpp>

#include "objects/entities/TIEntity.h"
#include "objects/components/CacheComponent.h"
#include "managers/ScriptManager.h"

using namespace TIE;

void CacheComponentSystem::update(const float delta) {
}


void CacheComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
    this->addComponent(tientity);
}


CacheComponent& CacheComponentSystem::addComponent(TIEntity& tientity) {
    CacheComponent& cacheComponent = tientity.addComponent<CacheComponent>();
    Components components = { cacheComponent };
    this->components.push_back(components);

    cacheComponent.setCache(ScriptManager::Instance()->getNewTable());

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


const std::string& CacheComponentSystem::getName() {
    return this->CACHE;
}


void CacheComponentSystem::updateCache(TIEntity& tientity, sol::table& cache) {
    CacheComponent* cacheComponent = tientity.getComponent<CacheComponent>();
    if (cacheComponent != nullptr) {
        cacheComponent->setCache(cache);
    }

}


sol::table& CacheComponentSystem::getCache(TIEntity& tientity) {
    CacheComponent* cacheComponent = tientity.getComponent<CacheComponent>();
    if (cacheComponent != nullptr) {
        return cacheComponent->getCache();
    } else {
    }
    return this->addComponent(tientity).getCache();
}
