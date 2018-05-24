#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "GlobalId.h"

namespace TIE {

class Player {
	public:
		Player(GlobalId id, sf::View& view);
		Player(sf::View& view);
		~Player();

		GlobalId getId() const;

		void setView(sf::View& view);
		sf::View& getView();
	private:	
		GlobalId id;
		sf::View& view;
};

}
#endif
