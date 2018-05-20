#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <map>
#include <memory>

#include "templates/Singleton.h"

#include "objects/Player.h"
#include "objects/GlobalId.h"

namespace TIE {

class PlayerManager : public Singleton<PlayerManager> {
	public:
		Player& addPlayer();
		Player& addPlayer(std::unique_ptr<Player> player);
		void rmPlayer(GlobalId id);

		Player& getPlayer(GlobalId id);
		const std::map<GlobalId, std::unique_ptr<Player> >& getAllPlayers();

		void registerId(std::string key, GlobalId id);
		GlobalId getRegisteredId(std::string key);

		PlayerManager();
		~PlayerManager();
	private:
		std::map<GlobalId, std::unique_ptr<Player> > players;
		std::map<std::string, GlobalId> registeredIds;

		PlayerManager(const PlayerManager&);
		void operator=(const PlayerManager&);
};

}
#endif
