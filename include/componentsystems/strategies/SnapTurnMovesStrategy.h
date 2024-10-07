#ifndef SNAPTURNMOVESSTRATEGY_H
#define SNAPTURNMOVESSTRATEGY_H

#include "componentsystems/strategies/MovesStrategy.h"

#include "objects/components/MovesComponent.h"
#include "objects/components/PositionComponent.h"

namespace TIE {

class SnapTurnMovesStrategy : public MovesStrategy {
    public:
        SnapTurnMovesStrategy() {};

        bool execute(const float, TIEntity&);

        const static inline std::string NAME = "SnapTurn";
    private:
        void accelerate(const float, MovesComponent&, PositionComponent&);
        void rotate(const float, MovesComponent&, PositionComponent&);
        bool move(const float, MovesComponent&, PositionComponent&);
};

}

#endif