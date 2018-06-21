#ifndef FACTORY_H
#define FACTORY_H

#include "managers/TIEntityManager.h"

#include "templates/MakeUnique.h"

namespace TIE {

template<typename T>
class Factory {
	public:

		GlobalId create() { 
			std::unique_ptr<T> ptr = TIE::make_unique<T>();
			GlobalId id = ptr->getId();
			return id;
		}

		GlobalId create(std::unique_ptr<T> ptr) {
			GlobalId id = ptr->getId();
			return id;
		}
};

}	
#endif
