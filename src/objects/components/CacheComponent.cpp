#include "objects\components\CacheComponent.h"

using namespace TIE;

void CacheComponent::setCache(const sol::table& cache) {
    this->cache = cache;
}

void CacheComponent::setCache(sol::table& cache) {
    this->cache = cache;
}


sol::table& CacheComponent::getCache() {
    return this->cache;
}
