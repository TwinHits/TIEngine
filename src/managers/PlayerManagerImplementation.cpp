#include "PlayerManager.h"
#include "HashManager.h"
#include "LogManager.h"

using namespace TIE;

PlayerManager::PlayerManager() {}
PlayerManager::~PlayerManager() 
{	
	for (auto i = players.begin(); i != players.end(); ++i)
	{
		rmPlayer(i->first);
	}	
}

const Player& PlayerManager::addPlayer()
{
	GlobalId id = HashManager::Instance()->getNewGlobalId();
	if (players.find(id) == players.end())
	{
		players[id] = new Player(id);
		LogManager::Instance()->logInfo("Added player '" + std::to_string(id) + "'.");
		return *players[id];
	}
	else 
	{
		LogManager::Instance()->logWarn("Hash collison! Player '" + std::to_string(id) + "' already exists, recursively rehashing.");
		return addPlayer();
	}	
}

void PlayerManager::rmPlayer(GlobalId id)
{
	if (players.find(id) != players.end())
	{
		delete players[id];
		LogManager::Instance()->logInfo("Deleted player '" + std::to_string(id) + "'.");
	}
	else 
	{
		LogManager::Instance()->logWarn("Player '" + std::to_string(id) + "' does not exist, doing nothing.");
	}
}

const Player& PlayerManager::getPlayer(GlobalId id)
{
	if (players.find(id) != players.end())
	{
		return *players[id];
	}
	else 
	{
		LogManager::Instance()->logError("Player '" + std::to_string(id) + "' does not exist, segfaulting.");
		return *players[id];
	}
}

const std::map<GlobalId, Player*>& PlayerManager::getAllPlayers()
{
	return players;
}
