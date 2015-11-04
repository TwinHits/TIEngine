#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <SFML/Graphics.hpp>

#include "../templates/Singleton.h"
#include "../objects/Player.h"

class WindowManager : public Singleton<WindowManager>
{
	public:
		sf::RenderWindow& addWindow();
		sf::RenderWindow& getWindow();
		void rmWindow();


		WindowManager();
		~WindowManager();

	private:
		
		sf::RenderWindow* window;

		WindowManager(const WindowManager&);
		void operator=(const WindowManager&);
};

#endif
