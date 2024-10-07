#ifndef MOVESSTRATEGY_H
#define MOVESSTRATEGY_H

#include "objects/tientities/TIEntity.h"

namespace TIE {

class MovesStrategy {
    public:
        MovesStrategy() {};
        virtual ~MovesStrategy() {};

        virtual bool execute(const float, TIEntity&) = 0;

};

}

#endif
