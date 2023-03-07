#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H

#include <memory>

#include "objects/GlobalId.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class FiniteStateMachine {
    public:
        FiniteStateMachine(TIEntity&);

        TIEntity& getTIEntity();

        GlobalId getOnEnterFunctionId();
        void setOnEnterFunctionId(GlobalId);

        GlobalId getOnUpdateFunctionId();
        void setOnUpdateFunctionId(GlobalId);

        GlobalId getOnExitFunctionId();
        void setOnExitFunctionId(GlobalId);

        void update(float);
        void onEnter();
        void onExit();

        void setState(std::unique_ptr<FiniteStateMachine>);

		static const inline std::string ON_ENTER = "onEnter";
		static const inline std::string ON_UPDATE = "onUpdate";
		static const inline std::string ON_EXIT = "onExit";

    private:

        void runFunction(GlobalId);

        TIEntity& tientity;
        std::unique_ptr<FiniteStateMachine> childState;
        GlobalId onEnterFunctionId = 0;
        GlobalId onUpdateFunctionId = 0;
        GlobalId onExitFunctionId = 0;
};

}

#endif
