#ifndef ACCELERATEDTURNMOVESSTRATEGY_H
#define ACCELERATEDTURNMOVESSTRATEGY_H

#include "componentsystems/strategies/MovesStrategy.h"

namespace TIE {

class AcceleratedTurnMovesStrategy : public MovesStrategy {
    public:
        AcceleratedTurnMovesStrategy() {};

        bool execute(const float, TIEntity&);

        const static inline std::string NAME = "AcceleratedTurn";

    private:
        void accelerateRotation(const float, MovesComponent&, PositionComponent&);
};

}

#endif