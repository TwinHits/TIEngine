#include <functional>

#include "HashManager.h"
#include "LogManager.h"

HashManager::HashManager() {}
HashManager::~HashManager() {}

unsigned long HashManager::getNewHash()
{
	++seed;
	return std::hash<unsigned long>()(seed);
}

void HashManager::setSeed(unsigned long seed)
{
	this->seed = seed;
	LogManager::Instance()->logInfo("Hash Seed set to '" + std::to_string(seed) + "'.");
}
