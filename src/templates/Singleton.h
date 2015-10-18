#ifndef SINGLETON_H
#define SINGLETON_H

class Singleton
{
	public:
		static Singleton& Instance()
		{
			instance = Singleton();
			return instance;
		}
		static Singleton instance;

	protected:
		Singleton() {}
		Singleton(const Singleton& S) {}
		~Singleton() {}
		void operator=(const Singleton& S) {}

};

#endif
