#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <map>

#include "../templates/Singleton.h"
#include "../objects/Player.h"

class PlayerManager : public Singleton<PlayerManager>
{
	public:
		const Player& addPlayer(unsigned long id);
		void rmPlayer(unsigned long id);

		const Player& getPlayer(unsigned long id);

		PlayerManager();
		~PlayerManager();
	private:
		std::map<unsigned long, Player*> players;

		PlayerManager(const PlayerManager&);
		void operator=(const PlayerManager&);
};

#endif
