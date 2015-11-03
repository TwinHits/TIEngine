#include "RenderWindow.h"

RenderWindow::RenderWindow(unsigned long id)
{
	this->id = id;
}

RenderWindow::~RenderWindow() {}

unsigned long RenderWindow::getId()
{
	return id;
}
