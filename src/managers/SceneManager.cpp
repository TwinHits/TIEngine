#include "managers/ConsoleManager.h"
#include "managers/SceneManager.h"
#include "managers/WindowManager.h"
#include "managers/TIEntityManager.h"
#include "managers/TimeManager.h"
#include "managers/ViewManager.h"


using namespace TIE;

SceneManager::SceneManager() {
	sceneViewId = ViewManager::Instance()->addView(sf::FloatRect(0,0,800,600));

}

	
SceneManager::~SceneManager() {

}


void SceneManager::render() {		
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
   	ViewManager::Instance()->setActiveView(sceneViewId);

	SceneNode& sceneGraph = TIEntityManager::Instance()->getSceneGraphRoot();
	sf::RenderStates states;

	window.clear();

	sceneGraph.draw(window, states);
	
	window.display();

}
