#ifndef TIENTITYINTERFACE_H
#define TIENTITYINTERFACE_H

#include "objects/entities/TIEntity.h"

#include <sol/sol.hpp>

namespace TIE {

class TIEntityInterface {
    public:
        TIEntityInterface(TIEntity&);
        ~TIEntityInterface() {};

        static void registerUserType(sol::state&);

        // Movement
        sf::Vector2f getPosition();
        void setDestination();
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