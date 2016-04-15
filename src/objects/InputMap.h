#ifndef INPUTMAP_H
#define INPUTMAP_H

#include <SFML/Graphics.hpp>

#include "../templates/Singleton.h"

namespace TIE
{
	class InputMap
	{
		public:
			virtual void processEvent(const sf::Event& Event);	
			virtual void processState();	

			InputMap();
			virtual ~InputMap();
		private:
	};
} 

#endif
