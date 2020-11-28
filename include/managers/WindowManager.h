#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

namespace TIE {

class WindowManager : public Singleton<WindowManager>, Manager {
	public:
		bool initialize();

		sf::RenderWindow& addWindow(sf::VideoMode mode=sf::VideoMode(1280, 720), 
									const std::string& title="Twin Ion Engine", 
									int style=sf::Style::Default,
									const sf::ContextSettings& settings=sf::ContextSettings());
		sf::RenderWindow& getWindow();
		sf::RenderWindow& updateWindowSize(const int, const int);
		void removeWindow();


		void showFPS(const std::string& fps);
		sf::Vector2i getWindowSize();

		const std::string& getTitle();
		void setTitle(const std::string&);

		WindowManager() {};
		~WindowManager();

	private:
		std::unique_ptr<sf::RenderWindow> window;
		std::string title;
		sf::Vector2i windowSize;

		WindowManager(const WindowManager&);
		void operator=(const WindowManager&) {};
};

}
#endif
