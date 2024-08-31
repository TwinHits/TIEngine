#include "managers/TimeManager.h"

#include "managers/HashManager.h"

using namespace TIE;

sf::Clock& TimeManager::addClock() {
	GlobalId id = HashManager::Instance()->getNewGlobalId();
    clocks[id] = sf::Clock();
    return clocks[id];
}


sf::Clock* TimeManager::getClock(GlobalId id) {
	if (this->clocks.count(id)) {
		return &this->clocks.at(id);
    } else {
        return nullptr;
    }
}
