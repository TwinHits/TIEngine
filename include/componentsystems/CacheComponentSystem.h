#ifndef CACHECOMPONENTSYSTEM_H
#define CACHECOMPONENTSYSTEM_H

#include "componentsystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include "objects/components/CacheComponent.h"
#include "objects/entities/TIEntity.h"

namespace TIE {

class CacheComponentSystem : public ComponentSystem, public Singleton<CacheComponentSystem> {
public:
    void update(const float);
    void addComponent(const TIEntityFactory&, TIEntity&);
    bool removeComponent(TIEntity&);
    const std::string& getName();

    bool setComponentProperty(const std::string&, bool, TIEntity&);
    bool setComponentProperty(const std::string&, float, TIEntity&);
    bool setComponentProperty(const std::string&, const std::string&, TIEntity&);
    sol::object getComponentProperty(const std::string&, TIEntity&);

    void updateCache(TIEntity&, sol::table&);
    sol::table& getCache(TIEntity&);

    static const inline std::string CACHE = "cache";
private:
    struct Components {
        CacheComponent& cacheComponent;
    };
    std::list<Components> components;

    CacheComponent& addComponent(TIEntity&);
};

}

#endif