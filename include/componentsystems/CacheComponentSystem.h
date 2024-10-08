#ifndef CACHECOMPONENTSYSTEM_H
#define CACHECOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include "objects/components/CacheComponent.h"

namespace TIE {

class CacheComponentSystem : public Singleton<CacheComponentSystem>, public OwnsComponent<CacheComponent> {
public:
    CacheComponentSystem();
    void update(const float);
    CacheComponent& addComponent(TIEntity&);
    CacheComponent& addComponent(const TIEntityFactory&, TIEntity&);
    bool removeComponent(TIEntity&);

    void updateCache(TIEntity&, sol::table&);
    sol::table& getCache(TIEntity&);

    void setCacheValue(TIEntity&, const std::string&, const sol::object&);
    sol::object getCacheValue(TIEntity&, const std::string&);
    sol::object getCacheValueOr(TIEntity&, const std::string&, const sol::object&);

    static const inline std::string CACHE = "cache";
private:
    struct Components {
        CacheComponent& cacheComponent;
    };
    std::list<Components> components;
};

}

#endif