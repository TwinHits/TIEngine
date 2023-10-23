#ifndef TIENTITYINTERFACE_H
#define TIENTITYINTERFACE_H

#include <string>

#include <sol/sol.hpp>

#include "interfaces/MessageInterface.h"
#include "objects/GlobalId.h"
#include "objects/components/structs/EventState.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class TIEntityInterface {
    public:
        TIEntityInterface(TIEntity&);
        TIEntityInterface(TIEntity*);
        ~TIEntityInterface() {};

        static void registerUserType(sol::state&);

        //Management
        GlobalId getId();
        std::string getName();
        void setName(const std::string&);
        sol::table& getChildren();
        sol::object getChild(const std::string&);
        sol::object getParent();
        sol::object spawn(const sol::table&);
        void despawn();

        //Common Child TIEntities
        void addTrace(const float, const float);
        void addCollisionBox(const float, const float, const float, const float);

        // Property
        void setProperty(const std::string&, const sol::object&);
        sol::object getProperty(const std::string&);

        // Rendering
        void setDrawn(bool);
        bool isDrawn();

        // Events
        void addState(const std::string&);
        void removeState(const std::string&);
        EventState* getState(const std::string&);

        // Cache
        void setCache(sol::table&);
        sol::table& getCache();
        void setCacheValue(const std::string&, const sol::object&);
        sol::object getCacheValue(const std::string&);
        sol::object getCacheValueOr(const std::string&, const sol::object&);

        // Search
        sol::table& findTIEntitiesWithinRange(const float, TIEntityInterface&);

        // Message
        void sendMessage(const GlobalId, sol::object, sol::object);

    private:
        TIEntity* tientity = nullptr;
        sol::table children = sol::table();
        sol::table tientitiesWithinRange = sol::table();
};

}

#endif