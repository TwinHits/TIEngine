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
			const T& create() 
			{ 
				T* ptr = new T();
				const T& ref = dynamic_cast<const T&>(SceneObjectManager::Instance()->addSceneObject(ptr));
				return ref;
			}
			const T& create(T* ptr)
			{
				const T& ref = dynamic_cast<const T&>(SceneObjectManager::Instance()->addSceneObject(ptr));
				return ref;
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
