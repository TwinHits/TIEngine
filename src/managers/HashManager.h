#ifndef HASHMANAGER_H
#define HASHMANAGER_H

#include "../templates/Singleton.h"

class HashManager : public Singleton<HashManager>
{
	public:
		unsigned long getNewHash();
		void setSeed(unsigned long seed);

		HashManager();
		~HashManager();

	private:
		unsigned long seed = 0;

		HashManager(const HashManager&);
		void operator=(const HashManager&);
};

#endif
