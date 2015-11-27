#include <functional>

#include "HashManager.h"
#include "LogManager.h"

using namespace TIE;

HashManager::HashManager() {}
HashManager::~HashManager() {}

GlobalId HashManager::getNewGlobalId()
{
	++seed;
	return seed;
}

void HashManager::setSeed(unsigned long seed)
{
	this->seed = seed;
	LogManager::Instance()->logInfo("Hash Seed set to '" + std::to_string(seed) + "'.");
}

GlobalId HashManager::getHash(const std::string& s)
{
	return std::hash<std::string>()(s);
}
