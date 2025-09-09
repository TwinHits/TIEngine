#ifndef STRATEGY_H
#define STRATEGY_H

#include "objects/tientities/TIEntity.h"

namespace TIE {

class Strategy {
    public:
        Strategy() {};
        virtual ~Strategy() {};

        virtual bool execute(const float, TIEntity&) = 0;
};

}

#endif
