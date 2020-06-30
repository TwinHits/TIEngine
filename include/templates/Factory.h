#ifndef FACTORY_H
#define FACTORY_H

#include "templates/MakeUnique.h"

namespace TIE {

template<typename T>
class Factory {
	public:

		TIEntity& create() { 
			std::unique_ptr<T> ptr = TIE::make_unique<T>();
			return *ptr;
		}

		TIEntity& create(std::unique_ptr<T> ptr) {
			return *ptr;
		}
};

}	
#endif
