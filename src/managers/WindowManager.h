#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <map>

#include "../templates/Singleton.h"
#include "../objects/Player.h"
#include "../objects/RenderWindow.h"

class WindowManager : public Singleton<WindowManager>
{
	public:
		RenderWindow& getWindow(unsigned long id);
		RenderWindow& addWindow();
		void rmWindow(unsigned long id);

		const std::map<unsigned long, RenderWindow*>& getAllWindows();

		WindowManager();
		~WindowManager();

	private:
		
		std::map<unsigned long, RenderWindow*> windows;

		WindowManager(const WindowManager&);
		void operator=(const WindowManager&);
};

#endif
