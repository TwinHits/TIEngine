#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <SFML/Graphics.hpp>

class RenderWindow : public sf::RenderWindow
{
	public:
		RenderWindow(unsigned long id);
		~RenderWindow();

		unsigned long getId();
	private:
		unsigned long id;

		RenderWindow(const RenderWindow&);
		void operator=(const RenderWindow&);
};

#endif
