#include "TimeManager.h"
#include "HashManager.h"
#include "LogManager.h"

using namespace TIE;

TimeManager::TimeManager() {}
TimeManager::~TimeManager() {}

const sf::Clock& TimeManager::addClock() 
{
	GlobalId id = HashManager::Instance()->getNewGlobalId();
	if (clocks.find(id) == clocks.end())
	{
		sf::Clock clock;
		clocks[id] = clock; 
		return clocks[id];
	}	
	else
	{
		LogManager::Instance()->logWarn("Hash collision! Player '" + std::to_string(id) + "' already exists, recursively rehashing.");
		return addClock();
	}
}

