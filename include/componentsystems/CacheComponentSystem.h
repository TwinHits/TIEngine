#ifndef CACHECOMPONENTSYSTEM_H
#define CACHECOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include "objects/components/CacheComponent.h"
#include "objects/tientities/TIEntity.h"

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

    static const inline std::string CACHE = "cache";
private:
    struct Components {
        CacheComponent& cacheComponent;
    };
    std::list<Components> components;
};

}

#endif