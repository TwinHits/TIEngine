#ifndef TIENTITYINTERFACE_H
#define TIENTITYINTERFACE_H

#include <string>

#include <sol/sol.hpp>

#include "interfaces/Vector2Interface.h"
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
        sol::table& getChildren();
        TIEntityInterface getParent();
        TIEntityInterface spawn(const sol::table&);
        void despawn();

        // Property
        void setProperty(const std::string&, const sol::object&);
        const std::string& getProperty(const std::string&);

        // Rendering
        void setDrawn(bool);
        bool isDrawn();

        // Movement
        Vector2fInterface getPosition();
        void setPosition(const float, const float);

        const float getRotation();
        void setRotation(const float);

        void setDestination(const float, const float);
        void setDestinationByDistance(const float);
        bool atDestination();

        void moveUp();
        void moveRight();
        void moveLeft();
        void moveDown();

        // Events
        void addState(const std::string&);
        void removeState(const std::string&);
        EventState* getState(const std::string&);

        // Cache
        void setCache(sol::table&);
        sol::table& getCache();

        // Behavior
        void setBehaviorById(GlobalId);
        void setBehaviorByName(const std::string&);

    private:
        TIEntity* tientity = nullptr;
        sol::table children = sol::table();
};

}

#endif