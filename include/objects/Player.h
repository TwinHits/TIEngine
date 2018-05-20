#ifndef PLAYER_H
#define PLAYER_H

#include "GlobalId.h"

namespace TIE {

class Player {
	public:
		Player();
		Player(GlobalId id);
		~Player();

		GlobalId getId() const;
	private:	
		GlobalId id;
};

}
#endif
