#include "managers/HashManager.h"

#include <functional>

#include "managers/LogManager.h"

using namespace TIE;

GlobalId HashManager::getNewGlobalId() {
	++seed;
	return seed;
}


void HashManager::setSeed(unsigned long seed) {
	this->seed = seed;
	LogManager::Instance()->info("Hash Seed set to '" + std::to_string(seed) + "'.");
}


GlobalId HashManager::getHash(const std::string& s) {
	return std::hash<std::string>()(s);
}
