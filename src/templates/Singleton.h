#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>

template <typename T>
class Singleton
{
	public:
		static T* Instance()
		{
			static T instance;
			return &instance;
		}

	protected:
		Singleton() {}
		Singleton(const Singleton& S) {}
		~Singleton() {}
		void operator=(const Singleton& S) {}
};

#endif
