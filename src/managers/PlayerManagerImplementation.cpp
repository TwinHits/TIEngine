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
	players[id] = new Player();
	LogManager::Instance()->logInfo("Added player '" + std::to_string(id) + "'.");
}

void PlayerManager::rmPlayer(int id)
{
	delete players[id];
	LogManager::Instance()->logInfo("Deleted player '" + std::to_string(id) + "'.");
}

const Player& getPlayer(int id)
{
	return players[id];
}
