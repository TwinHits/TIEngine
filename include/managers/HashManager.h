#ifndef HASHMANAGER_H
#define HASHMANAGER_H

#include "templates/Singleton.h"

#include <string>

#include "objects/GlobalId.h"

namespace TIE {

	class HashManager : public Singleton<HashManager> {
	public:
		GlobalId getNewGlobalId();
		GlobalId getHash(const std::string& s);

		void setSeed(unsigned long seed);

		HashManager() {};
		~HashManager() {};

	private:
		GlobalId seed = 0;

		HashManager(const HashManager&);
		void operator=(const HashManager&) {};
};

}
#endif
