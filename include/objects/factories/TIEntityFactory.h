#ifndef TIENTITYFACTORY_H
#define TIENTITYFACTORY_H

#include <map>
#include <vector>
#include <string>

#include <sol/sol.hpp>

#include "objects/entities/TIEntity.h" 
#include "objects/GlobalId.h"

namespace TIE {

class TIEntityFactory {
	public:
		TIEntityFactory() {};
		TIEntityFactory(const sol::table&);

		TIEntityFactory& setName(std::string);
		const std::string& getName();

		TIEntityFactory& setParent(TIEntity*);
		TIEntityFactory& addChild();

		TIEntityFactory& addComponentSystemByComponentName(const std::string&);

		std::map<std::string, bool> boolValues;
		std::map<std::string, float> floatValues;
		std::map<std::string, std::string> stringValues;
		std::map<std::string, GlobalId> functionValues;

		TIEntity& build();

		static const inline std::string NAME = "tientity.name";

		~TIEntityFactory() {};

	private:
		std::string name = "";
		TIEntity* parent = nullptr;
		std::vector<TIEntityFactory> children;
		std::map<std::string, bool> componentSystemNames;
};

}
#endif
