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
		TIEntityFactory();

		TIEntity& build();

		TIEntityFactory& setName(std::string);
		TIEntityFactory& setParent(TIEntity*);
		TIEntityFactory& registerChild();

		bool isValidComponentName(const std::string&);

		std::map<std::string, bool> boolValues;
		std::map<std::string, float> floatValues;
		std::map<std::string, std::string> stringValues;
		std::map<std::string, GlobalId> functionValues;

		~TIEntityFactory() {};

	private:
		std::string name = "";
		TIEntity* parent = nullptr;
		std::vector<TIEntityFactory> children;

		std::vector<std::string> validComponentNames;
		static const inline std::string LIFECYCLE = "lifecycle";
		static const inline std::string LIFECYCLE_CREATED = LIFECYCLE + ".created";
};

}
#endif
