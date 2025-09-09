#ifndef FORWARDPATHSSTRATEGY_H
#define FORWARDPATHSSTRATEGY_H

#include "componentsystems/strategies/paths/PathsStrategy.h"

namespace TIE {

class ForwardPathsStrategy : public PathStrategy {
    public:
        ForwardPathsStrategy() {};

        bool execute(const float, TIEntity&);

		static const inline std::string NAME = "Forward";
    private:
};

}

#endif
