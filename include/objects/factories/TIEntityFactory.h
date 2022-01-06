#ifndef TIENTITYFACTORY_H
#define TIENTITYFACTORY_H

#include <map>
#include <vector>
#include <string>

#include "objects/entities/TIEntity.h" 
#include "objects/GlobalId.h"

namespace TIE {

class TIEntityFactory {
	public:
		TIEntityFactory& setName(std::string);
		TIEntityFactory& setParent(TIEntity*);
		TIEntityFactory& registerChild();

		std::map<std::string, bool> boolValues;
		std::map<std::string, float> floatValues;
		std::map<std::string, std::string> stringValues;
		std::map<std::string, GlobalId> functionValues;

		TIEntity& build();

		TIEntityFactory() {};
		~TIEntityFactory() {};

	private:
		std::string name = "";
		TIEntity* parent = nullptr;
		std::vector<TIEntityFactory> children;

};

}
#endif
