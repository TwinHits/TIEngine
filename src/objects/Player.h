#ifndef PLAYER_H
#define PLAYER_H

class Player
{
	public:
		Player(int id);
		~Player();

		int getId() const;
	private:	
		int id;

		Player(const Player&);
		void operator=(const Player&);
};

#endif
