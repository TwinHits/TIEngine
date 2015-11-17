#ifndef FACTORY_H
#define FACTORY_H

#include "../managers/SceneObjectManager.h"

template<typename T>
class Factory
{
	public:
		const T& create() 
		{ 
			T* so_ptr = new T();
			const T& so = dynamic_cast<const T&>(SceneObjectManager::Instance()->addSceneObject(so_ptr));
			return so;
		}

	protected:
		Factory() {}
		Factory(const Factory& F) {}
		void operator=(const Factory& F) {}
		~Factory() {}

	private:

};

#endif
