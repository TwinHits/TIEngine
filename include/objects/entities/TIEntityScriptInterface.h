#ifndef TIENTITYSCRIPTINTERFACE_H
#define TIENTITYSCRIPTINTERFACE_H

#include "objects/entities/TIEntity.h"

namespace TIE {

class TIEntityScriptInterface {
    public:
        TIEntityScriptInterface(TIEntity&);
        ~TIEntityScriptInterface() {};

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