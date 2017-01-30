#include "managers/PlayerManager.h"
#include "managers/HashManager.h"
#include "managers/LogManager.h"

using namespace TIE;

PlayerManager::PlayerManager() {}
PlayerManager::~PlayerManager() {}

const Player& PlayerManager::addPlayer()
{
	GlobalId id = HashManager::Instance()->getNewGlobalId();
	if (players.find(id) == players.end())
	{
		players[id] = std::make_shared<Player>(id);
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
	auto player = players.find(id);
	if (player != players.end())
	{
		players.erase(player);	
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

const std::map<GlobalId, std::shared_ptr<Player> >& PlayerManager::getAllPlayers()
{
	return players;
}
