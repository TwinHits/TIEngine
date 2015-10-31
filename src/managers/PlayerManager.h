#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <map>

#include "../templates/Singleton.h"
#include "../objects/Player.h"

class PlayerManager : public Singleton<PlayerManager>
{
	public:
		void addPlayer();
		void rmPlayer();

		const Player& getPlayer(int id);

		PlayerManager();
		~PlayerManager();
	private:
		std::Map<int, Player*> players;

		PlayerManager(const PlayerManager&);
		void operator=(const PlayerManager&);
};

#endif
