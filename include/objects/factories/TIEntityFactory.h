#ifndef TIENTITYFACTORY_H
#define TIENTITYFACTORY_H

#include <array>
#include <map>
#include <string>

#include "objects/entities/TIEntity.h" 

namespace TIE {

class TIEntityFactory {
	public:
		TIEntityFactory();

		TIEntity& build();

		TIEntityFactory& setName(std::string);
		TIEntityFactory& setParent(TIEntity*);

		bool isValidComponentName(const std::string&);

		std::map<std::string, bool> boolValues;
		std::map<std::string, float> floatValues;
		std::map<std::string, std::string> stringValues;

		~TIEntityFactory() {};

	private:
		TIEntity* parent = nullptr;
		std::string name = "";

		std::array<std::string, 6> validComponentNames;
};

}
#endif
