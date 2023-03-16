#ifndef OWNSCOMPONENT_H
#define OWNSCOMPONENT_H

#include "componentsystems/ComponentSystem.h"

#include "objects/tientities/TIEntity.h"
#include "objects/GlobalId.h"

namespace TIE {

template <typename T>
class OwnsComponent : public ComponentSystem {
	public:
	    virtual ~OwnsComponent() {};

        virtual bool hasComponent(const TIEntity& tientity) {
            return tientity.hasComponent<T>();
        }
};

}
#endif