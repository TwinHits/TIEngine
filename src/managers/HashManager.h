#ifndef HASHMANAGER_H
#define HASHMANAGER_H

#include "../templates/Singleton.h"

#include "../objects/GlobalId.h"

class HashManager : public Singleton<HashManager>
{
	public:
		GlobalId getNewGlobalId();
		unsigned long getHash(const std::string& s);

		void setSeed(unsigned long seed);

		HashManager();
		~HashManager();

	private:
		unsigned long seed = 0;

		HashManager(const HashManager&);
		void operator=(const HashManager&);
};

#endif
