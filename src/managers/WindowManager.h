#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <map>

#include <SFML/Graphics.hpp>

#include "../templates/Singleton.h"

class WindowManager : public Singleton<WindowManager>
{
	public:
		sf::RenderWindow& getWindow(int id);
		void addWindow(int id);
		void rmWindow(int id);

		WindowManager();
		~WindowManager();

	private:
		
		std::map<int, sf::RenderWindow*> playerWindows;

		WindowManager(const WindowManager&);
		void operator=(const WindowManager&);
};

#endif
