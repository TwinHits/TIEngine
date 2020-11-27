#ifndef TIENTITYINTERFACE_H
#define TIENTITYINTERFACE_H

#include "objects/entities/TIEntity.h"

namespace TIE {

class TIEntityInterface {
    public:
        TIEntityInterface(TIEntity&);
        ~TIEntityInterface() {};

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