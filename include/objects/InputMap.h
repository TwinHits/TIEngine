#ifndef INPUTMAP_H
#define INPUTMAP_H

#include <SFML/Graphics.hpp>

#include "templates/Singleton.h"

namespace TIE
{
	class InputMap
	{
		public:
			virtual void processEvent(const sf::Event& Event, const sf::Vector2f& position);
			virtual void processState(const sf::Vector2f& position);

			InputMap();
			virtual ~InputMap();
		private:
	};
} 

#endif
