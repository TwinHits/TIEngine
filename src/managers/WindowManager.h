#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <string>

#include <SFML/Graphics.hpp>

#include "../templates/Singleton.h"

class WindowManager : public Singleton<WindowManager>
{
	public:
		sf::RenderWindow& addWindow(sf::VideoMode mode=sf::VideoMode(800, 600), const std::string& title="Twin Ion Engine", int style=sf::Style::Default, const sf::ContextSettings& settings=sf::ContextSettings());
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
