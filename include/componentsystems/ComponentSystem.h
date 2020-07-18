#ifndef COMPONENTSYSTEM_H
#define COMPONENTSYSTEM_H

#include "objects/entities/TIEntity.h"

namespace TIE {

class ComponentSystem {
	public:
		virtual ~ComponentSystem() {};
		virtual void update(TIEntity&, const float) = 0;
};

}
#endif