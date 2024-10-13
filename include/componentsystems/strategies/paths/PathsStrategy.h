#ifndef PATHSTRATEGY_H
#define PATHSTRATEGY_H

#include "componentsystems/strategies/Strategy.h"

namespace TIE {

class PathStrategy : public Strategy {
    public:
        PathStrategy() {};

        bool execute(const float, TIEntity&);

    private:
};

}

#endif
