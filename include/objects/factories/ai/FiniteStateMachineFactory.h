#ifndef FINITESTATEMACHINEFACTORY_H
#define FINITESTATEMACHINEFACTORY_H

#include <sol/sol.hpp>

#include <map>
#include <memory>
#include <string>

#include "objects/GlobalId.h"
#include "objects/ai/FiniteStateMachine.h"

namespace TIE {

class FiniteStateMachineFactory {
	public:
		FiniteStateMachineFactory(const sol::table&);

		std::unique_ptr<FiniteStateMachine> build(TIEntity&);

		GlobalId getId();

		std::map<std::string, GlobalId> stringToFunctionValues;
		std::map<GlobalId, GlobalId> idToFunctionValues;
	private:
		GlobalId id = 0;
};

}

#endif FINITESTATEMACHINEFACTORY_H
