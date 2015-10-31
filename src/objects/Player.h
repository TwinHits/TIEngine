#ifndef PLAYER_H
#define PLAYER_H

class Player
{
	public:
		Player();
		~Player();
	private:	
		Player(const Player&);
		void operator=(const Player&);
};

#endif
