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
	players[id] = new Player(id);
	LogManager::Instance()->logInfo("Added player '" + std::to_string(id) + "'.");
	WindowManager::Instance()->addWindow(id);
}

void PlayerManager::rmPlayer(int id)
{
	WindowManager::Instance()->rmWindow(id);
	delete players[id];
	LogManager::Instance()->logInfo("Deleted player '" + std::to_string(id) + "'.");
}

const Player& PlayerManager::getPlayer(int id)
{
	return *players[id];
}
