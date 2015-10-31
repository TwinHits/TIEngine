#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <map>

#include <SFML/Graphics.hpp>

#include "../templates/Singleton.h"
#include "../objects/Player.h"

class WindowManager : public Singleton<WindowManager>
{
	public:
		sf::RenderWindow& getWindow(unsigned long id);
		sf::RenderWindow& addWindow(unsigned long id);
		void rmWindow(unsigned long id);

		WindowManager();
		~WindowManager();

	private:
		
		std::map<unsigned long, sf::RenderWindow*> playerWindows;

		WindowManager(const WindowManager&);
		void operator=(const WindowManager&);
};

#endif
