#include "managers/SceneManager.h"
#include "managers/WindowManager.h"
#include "managers/TIEntityManager.h"
#include "managers/TimeManager.h"
#include "managers/ViewManager.h"


using namespace TIE;

SceneManager::SceneManager() {

}

	
SceneManager::~SceneManager() {

}


void SceneManager::render() {		
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();

	SceneNode& sceneGraph = TIEntityManager::Instance()->getSceneGraphRoot();
	sf::RenderStates states;

	window.clear();
	sceneGraph.draw(window, states);
	window.display();
}
