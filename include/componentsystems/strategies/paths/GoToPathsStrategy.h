#ifndef GOTOPATHSSTRATEGY_H
#define GOTOPATHSSTRATEGY_H

#include "componentsystems/strategies/paths/PathsStrategy.h"

namespace TIE {

class GoToPathsStrategy : public PathStrategy {
    public:
        GoToPathsStrategy() {};

        bool execute(const float, TIEntity&);

		static const inline std::string NAME = "GoTo";
    private:
};

}

#endif
