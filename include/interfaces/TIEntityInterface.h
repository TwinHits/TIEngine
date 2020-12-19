#ifndef TIENTITYINTERFACE_H
#define TIENTITYINTERFACE_H

#include "objects/entities/TIEntity.h"

#include <sol/sol.hpp>

#include "interfaces/Vector2Interface.h"

namespace TIE {

class TIEntityInterface {
    public:
        TIEntityInterface(TIEntity&);
        ~TIEntityInterface() {};

        static void registerUserType(sol::state&);

        // Movement
        Vector2fInterface getPosition();
        void setDestination(const float, const float);
        bool atDestination();
        void moveUp();
        void moveRight();
        void moveLeft();
        void moveDown();

        // Spawn
        void spawn(const std::string&);
        void despawn();

        // Events
        void addState(const std::string&);
        void removeState(const std::string&);

        // Cache
        void setCache(sol::table&);
        sol::table& getCache();

    private:
        TIEntity* tientity = nullptr;
};

}

#endif