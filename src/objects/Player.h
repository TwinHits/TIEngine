#ifndef PLAYER_H
#define PLAYER_H

class Player
{
	public:
		Player(unsigned long id);
		~Player();

		unsigned long getId() const;
	private:	
		unsigned long id;

		Player(const Player&);
		void operator=(const Player&);
};

#endif
