#ifndef FACTORY_H
#define FACTORY_H

#include "../managers/SceneObjectManager.h"

using namespace TIE;

namespace TIE
{
	template<typename T>
	class Factory
	{
		public:
			const T& create_ref() 
			{ 
				T* ptr = new T();
				const T& ref = dynamic_cast<const T&>(SceneObjectManager::Instance()->addSceneObject(ptr));
				return ref;
			}
			const T& create_ref(T* ptr)
			{
				const T& ref = dynamic_cast<const T&>(SceneObjectManager::Instance()->addSceneObject(ptr));
				return ref;
			}
			const T* create_ptr() 
			{ 
				const T* ptr = new T();
				SceneObjectManager::Instance()->addSceneObject(ptr);
				return ptr;
			}
			const T* create_ptr(T* ptr)
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
