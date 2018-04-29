#ifndef FACTORY_H
#define FACTORY_H

#include "managers/TIEntityManager.h"

namespace TIE {

template<typename T>
class Factory {
	public:
		GlobalId create() { 
			std::unique_ptr<T> ptr = std::make_unique<T>();
			GlobalId id = ptr->getId();
			TIEntityManager::Instance()->addTIEntity(std::move(ptr));
			return id;
		}
		GlobalId create(std::unique_ptr<T> ptr) {
			GlobalId id = ptr->getId();
			TIEntityManager::Instance()->addTIEntity(std::move(ptr));
			return id;
		}
};

}	
#endif
