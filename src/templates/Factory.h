#ifndef FACTORY_H
#define FACTORY_H

#include "../managers/SceneObjectManager.h"

namespace TIE
{
	template<typename T>
	class Factory
	{
		public:
			const T& create_ref() 
			{ 
				std::shared_ptr<T> ptr = std::make_shared<T>();
				const T& ref = dynamic_cast<const T&>(SceneObjectManager::Instance()->addSceneObject(ptr));
				return ref;
			}
			const T& create_ref(std::shared_ptr<T> ptr)
			{
				const T& ref = dynamic_cast<const T&>(SceneObjectManager::Instance()->addSceneObject(ptr));
				return ref;
			}
			const std::shared_ptr<T> create_ptr() 
			{ 
				std::shared_ptr<T> ptr = std::make_shared<T>();
				SceneObjectManager::Instance()->addSceneObject(ptr);
				return ptr;
			}
			const std::shared_ptr<T> create_ptr(std::shared_ptr<T> ptr)
			{
				SceneObjectManager::Instance()->addSceneObject(ptr);
				return ptr;
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
