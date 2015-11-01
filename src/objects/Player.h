#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{
	public:
		Player(int id);
		~Player();

		int getId() const;
		sf::RenderWindow& getWindow() const;
	private:	
		int id;
		sf::RenderWindow* window;

		Player(const Player&);
		void operator=(const Player&);
};

#endif
