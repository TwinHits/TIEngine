#ifndef COMPONENTSYSTEM_H
#define COMPONENTSYSTEM_H

#include <string>

#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"

namespace TIE {

class ComponentSystem {
	public:
		virtual ~ComponentSystem() {};
		virtual void update(const float) = 0;
		virtual void addComponent(const TIEntityFactory&, TIEntity&) = 0;
		virtual const std::string& getName() = 0;
};

}
#endif