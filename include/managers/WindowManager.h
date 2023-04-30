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

		sf::RenderWindow& addWindow(const sf::Vector2i& size, const std::string&, const int);
		sf::RenderWindow& addWindow(const std::string&);
		sf::RenderWindow& addWindow(const int);
		sf::RenderWindow& addWindow();

		sf::RenderWindow& getWindow();
		void removeWindow();

		sf::RenderWindow& updateWindowSize(const int, const int);
		sf::RenderWindow& updateFullScreen(const bool);
		const sf::Vector2i& getWindowSize();

		const std::string& getTitle();
		void setTitle(const std::string&);

		void setStyle(const int);
		const int getStyle();

		void setFullScreen(const bool);
		const bool getFullScreen();

		WindowManager() {};
		~WindowManager();

	private:
		std::unique_ptr<sf::RenderWindow> window;

		std::string title = "Twin Ion Engine";
		sf::Vector2i windowSize = sf::Vector2i(1280, 720);
		int style = sf::Style::Default;

		WindowManager(const WindowManager&);
		void operator=(const WindowManager&) {};
};

}
#endif
