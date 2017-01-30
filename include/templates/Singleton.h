#ifndef SINGLETON_H
#define SINGLETON_H

namespace TIE
{
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
			void operator=(const Singleton& S) {}
			~Singleton() {}
	};
}

#endif
