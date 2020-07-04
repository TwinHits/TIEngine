#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include "templates/Singleton.h"

#include <SFML/Graphics.hpp>

#include "objects/GlobalId.h"

namespace TIE {

class TimeManager : public Singleton<TimeManager> {
	public:
		sf::Clock& addClock();	
		sf::Clock& getClock(GlobalId id);

		TimeManager();
		~TimeManager();

	private:
		std::map<GlobalId, sf::Clock> clocks;

		sf::Clock& addClock(GlobalId id);

		TimeManager(const TimeManager&);
		void operator=(const TimeManager&) {};
};

}
#endif
