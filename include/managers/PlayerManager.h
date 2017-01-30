#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <map>
#include <memory>

#include "templates/Singleton.h"

#include "objects/Player.h"
#include "objects/GlobalId.h"

namespace TIE
{

	class PlayerManager : public Singleton<PlayerManager>
	{
		public:
			const Player& addPlayer();
			void rmPlayer(GlobalId id);

			const Player& getPlayer(GlobalId id);
			const std::map<GlobalId, std::shared_ptr<Player> >& getAllPlayers();

			PlayerManager();
			~PlayerManager();
		private:
			std::map<GlobalId, std::shared_ptr<Player> > players;
	
			PlayerManager(const PlayerManager&);
			void operator=(const PlayerManager&);
	};

}
	
#endif
