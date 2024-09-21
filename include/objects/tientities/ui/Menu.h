#ifndef MENU_H
#define MENU_H

#include "objects/tientities/TIEntity.h"

#include "objects/Message.h"

namespace TIE {

class Menu : public TIEntity {
    public:
        Menu() {};
        ~Menu() {};

        void onClick(Message&);
    private:
        bool show = false;

};

}

#endif