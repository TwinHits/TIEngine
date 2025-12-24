#ifndef PATHSTRATEGY_H
#define PATHSTRATEGY_H

#include "componentsystems/strategies/Strategy.h"

namespace TIE {

class PathStrategy : public Strategy {
    public:
        PathStrategy() {};

        virtual bool execute(const float, TIEntity&) = 0;

    private:
};

}

#endif
