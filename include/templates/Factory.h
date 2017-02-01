#ifndef FACTORY_H
#define FACTORY_H

#include "managers/TIEntityManager.h"

namespace TIE
{
	template<typename T>
	class Factory
	{
		public:
			T* create() 
			{ 
				std::shared_ptr<T> ptr = std::make_shared<T>();
				TIEntityManager::Instance()->addTIEntity(ptr);
				return ptr.get();
			}
			T* create(std::shared_ptr<T> ptr)
			{
				TIEntityManager::Instance()->addTIEntity(ptr);
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
