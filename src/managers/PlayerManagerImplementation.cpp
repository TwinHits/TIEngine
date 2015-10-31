#include "PlayerManager.h"
#include "WindowManager.h"
#include "LogManager.h"

PlayerManager::PlayerManager() {}
PlayerManager::~PlayerManager() 
{	
	for (auto i = players.begin(); i != players.end(); ++i)
	{
		rmPlayer(i->first);
	}	
}

void PlayerManager::addPlayer(int id)
{
	if (players.find(id) == players.end())
	{
		players[id] = new Player(id);
		LogManager::Instance()->logInfo("Added player '" + std::to_string(id) + "'.");
		WindowManager::Instance()->addWindow(id);
	}
	else 
	{
		LogManager::Instance()->logWarn("Player '" + std::to_string(id) + "' already exists, doing nothing.");
	}	
}

void PlayerManager::rmPlayer(int id)
{
	WindowManager::Instance()->rmWindow(id);
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

const Player& PlayerManager::getPlayer(int id)
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
