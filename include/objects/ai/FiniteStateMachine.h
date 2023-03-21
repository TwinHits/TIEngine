#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H

#include <memory>

#include "objects/GlobalId.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class FiniteStateMachine {
    public:
        FiniteStateMachine(TIEntity&, const GlobalId);

        void setParent(FiniteStateMachine*);
        FiniteStateMachine* getParent();

        TIEntity& getTIEntity();
        const GlobalId getFactoryId();

        const GlobalId getOnEnterFunctionId();
        void setOnEnterFunctionId(const GlobalId);

        const GlobalId getOnUpdateFunctionId();
        void setOnUpdateFunctionId(const GlobalId);

        const GlobalId getOnExitFunctionId();
        void setOnExitFunctionId(const GlobalId);

        void setExit(bool);
        bool getExit();

        void update(float);
        void onEnter();
        void onExit();

        void setState(std::unique_ptr<FiniteStateMachine>);

		static const inline std::string ON_ENTER = "onEnter";
		static const inline std::string ON_UPDATE = "onUpdate";
		static const inline std::string ON_EXIT = "onExit";

    private:
        void runFunction(const GlobalId, const float);
        void runFunction(const GlobalId);

        TIEntity& tientity;
        GlobalId factoryId;
        FiniteStateMachine* parent = nullptr;
        std::unique_ptr<FiniteStateMachine> childState;

        GlobalId onEnterFunctionId = 0;
        GlobalId onUpdateFunctionId = 0;
        GlobalId onExitFunctionId = 0;

        bool exit = false;
};

}

#endif
