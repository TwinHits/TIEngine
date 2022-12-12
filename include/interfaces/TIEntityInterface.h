#ifndef TIENTITYINTERFACE_H
#define TIENTITYINTERFACE_H

#include <string>

#include <sol/sol.hpp>

#include "objects/GlobalId.h"
#include "objects/components/structs/EventState.h"
#include "objects/entities/TIEntity.h"

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
        TIEntityInterface getParent();
        TIEntityInterface spawn(const sol::table&);
        void despawn();

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

    private:
        TIEntity* tientity = nullptr;
        sol::table children = sol::table();
};

}

#endif