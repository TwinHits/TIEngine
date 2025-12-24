#ifndef STEADYMOVESSTRATEGY_H
#define STEADYMOVESSTRATEGY_H

#include "componentsystems/strategies/moves/MovesStrategy.h"

namespace TIE {

class SteadyMovesStrategy : public MovesStrategy {
    public:
        SteadyMovesStrategy() {};

        bool execute(const float, TIEntity&);

        const static inline std::string NAME = "Steady";

    private:
        void accelerate(const float, MovesComponent&, PositionComponent&);
        void accelerateRotation(const float, MovesComponent&, PositionComponent&);
};

}

#endif
