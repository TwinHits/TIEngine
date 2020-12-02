#ifndef TIENTITYINTERFACE_H
#define TIENTITYINTERFACE_H

#include "objects/entities/TIEntity.h"

#include <sol/sol.hpp>

#include "interfaces/Vector2fInterface.h"

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

    private:
        TIEntity* tientity = nullptr;
};

}

#endif