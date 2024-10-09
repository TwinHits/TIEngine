#ifndef SNAPTURNMOVESSTRATEGY_H
#define SNAPTURNMOVESSTRATEGY_H

#include "componentsystems/strategies/MovesStrategy.h"

namespace TIE {

class SnapTurnMovesStrategy : public MovesStrategy {
    public:
        SnapTurnMovesStrategy() {};

        bool execute(const float, TIEntity&);

        const static inline std::string NAME = "SnapTurn";
    private:
        void rotate(const float, MovesComponent&, PositionComponent&);
};

}

#endif