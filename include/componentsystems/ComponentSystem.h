#ifndef COMPONENTSYSTEM_H
#define COMPONENTSYSTEM_H

#include "objects/entities/TIEntity.h"

namespace TIE {

class ComponentSystem {
	public:
		virtual ~ComponentSystem() {};
		virtual void execute(TIEntity&, const float) = 0;
};

}
#endif