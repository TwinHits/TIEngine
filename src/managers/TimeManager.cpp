#include "managers/TimeManager.h"
#include "managers/HashManager.h"
#include "managers/LogManager.h"

using namespace TIE;

TimeManager::TimeManager() {

}


TimeManager::~TimeManager() {

}


sf::Clock& TimeManager::addClock() {
	GlobalId id = HashManager::Instance()->getNewGlobalId();
	return this->addClock(id);
}


sf::Clock& TimeManager::getClock(GlobalId id) {
	if (clocks.find(id) == clocks.end()) {
		return clocks[id];
	} else {
		TIE::LogManager::Instance()->warn("No id exists for id " + std::to_string(id) + ". Adding new clock and returning it.");
		return this->addClock(id);
	}
}


sf::Clock& TIE::TimeManager::addClock(GlobalId id) {
	if (clocks.find(id) == clocks.end()) {
		sf::Clock clock;
		clocks[id] = clock; 
		return clocks[id];
	} else {
		LogManager::Instance()->warn("Hash collision! Player '" + std::to_string(id) + "' already exists, recursively rehashing.");
		return addClock();
	}
}