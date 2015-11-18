#ifndef PLAYER_H
#define PLAYER_H

#include "GlobalId.h"

class Player
{
	public:
		Player(GlobalId id);
		~Player();

		GlobalId getId() const;
	private:	
		GlobalId id;

		Player(const Player&);
		void operator=(const Player&);
};

#endif
