#ifndef MOVESSTRATEGY_H
#define MOVESSTRATEGY_H

#include "componentsystems/strategies/Strategy.h"

#include "objects/components/MovesComponent.h"
#include "objects/components/PathsComponent.h"
#include "objects/components/PositionComponent.h"

namespace TIE {

class MovesStrategy : public Strategy {
    public:
        MovesStrategy() {};
        virtual ~MovesStrategy() {};

    protected:
        virtual void accelerate(const float, MovesComponent&, PathsComponent&, PositionComponent&);
        virtual void rotate(const float, MovesComponent&, PathsComponent&, PositionComponent&);
        virtual bool move(const float, MovesComponent&, PathsComponent&, PositionComponent&);

};

}

#endif
