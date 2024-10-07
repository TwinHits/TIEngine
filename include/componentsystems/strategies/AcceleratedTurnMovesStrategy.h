#ifndef ACCELERATEDTURNMOVESSTRATEGY_H
#define ACCELERATEDTURNMOVESSTRATEGY_H

#include "componentsystems/strategies/MovesStrategy.h"

#include "objects/components/MovesComponent.h"
#include "objects/components/PositionComponent.h"

namespace TIE {

class AcceleratedTurnMovesStrategy : public MovesStrategy {
    public:
        AcceleratedTurnMovesStrategy() {};

        bool execute(const float, TIEntity&);

        const static inline std::string NAME = "AcceleratedTurn";

    private:
        void accelerateRotation(const float, MovesComponent&, PositionComponent&);
        void accelerate(const float, MovesComponent&, PositionComponent&);
        void rotate(const float, MovesComponent&, PositionComponent&);
        bool move(const float, MovesComponent&, PositionComponent&);
};

}

#endif