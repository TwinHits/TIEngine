#ifndef INPUTMAP_H
#define INPUTMAP_H

#include <SFML/Graphics.hpp>

#include "../templates/Singleton.h"

namespace TIE
{
	class InputMap
	{
		public:
			virtual void process(const sf::Event& Event);	

			InputMap();
			virtual ~InputMap();
		private:
	};
} 

#endif
