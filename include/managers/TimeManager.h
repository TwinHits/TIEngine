#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <SFML/Graphics.hpp>

#include "objects/GlobalId.h"

#include "templates/Singleton.h"

namespace TIE
{

	class TimeManager : public Singleton<TimeManager>
	{
		public:
			sf::Clock& addClock();	

			TimeManager();
			~TimeManager();

		private:
			std::map<GlobalId, sf::Clock> clocks;

			TimeManager(const TimeManager&);
			void operator=(const TimeManager&);
	};
}

#endif
