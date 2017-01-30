#ifndef FACTORY_H
#define FACTORY_H

#include "../managers/SceneObjectManager.h"

namespace TIE
{
	template<typename T>
	class Factory
	{
		public:
			T* create() 
			{ 
				std::shared_ptr<T> ptr = std::make_shared<T>();
				SceneObjectManager::Instance()->addSceneObject(ptr);
				return ptr.get();
			}
			T* create(std::shared_ptr<T> ptr)
			{
				SceneObjectManager::Instance()->addSceneObject(ptr);
				return ptr.get();
			}
	
		protected:
			Factory() {}
			Factory(const Factory& F) {}
			void operator=(const Factory& F) {}
			~Factory() {}
	
		private:
	
	};
}	

#endif
