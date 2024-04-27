#include "managers/InputManager.h" 

#include <cstdio>

#include <SFML/Graphics.hpp>

#include "componentsystems/EventsComponentSystem.h"
#include "componentsystems/MessagesComponentSystem.h"
#include "managers/MessageManager.h"
#include "managers/LogManager.h"
#include "managers/SceneManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"
#include "objects/Message.h"
#include "utils/constants/SfEventStringMap.h"

using namespace TIE;

const sf::Vector2f& InputManager::getMouseWindowPosition() {
	return this->mouseWindowPosition;
}


const sf::Vector2f& InputManager::getMouseWorldPosition() {
	return this->mouseWorldPosition;
}


const sf::Event* const InputManager::getEvent(const sf::Event::EventType& eventType) {
	if (this->events.find(eventType) != events.end()) {
		return &(events.at(eventType));
	}
	return nullptr;
}


void InputManager::processInput() {
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::View& clientView = ViewManager::Instance()->getClientView();
	this->mouseWindowPosition = window.mapPixelToCoords(mousePosition);
	this->mouseWorldPosition = window.mapPixelToCoords(mousePosition, clientView); 
	this->events.clear();

	sf::Event event;
	while (window.pollEvent(event)) {

		//Window Input Commands
		if (!consoleManager->checkConsole()) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				LogManager::Instance()->debug("Window closed by X.");
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					window.close();
					LogManager::Instance()->debug("Window closed by escape.");
					break;
				case sf::Keyboard::Home:
					SceneManager::Instance()->setSimulationPaused(!SceneManager::Instance()->isSimulationPaused());
					break;
				case sf::Keyboard::Tilde:
					consoleManager->showConsole();
					break;
				default:
					this->events.insert({ event.type, event });
					break;
				}
				break;
			case sf::Event::MouseButtonPressed:
				event.mouseButton.x = this->mouseWorldPosition.x;
				event.mouseButton.y = this->mouseWorldPosition.y;
				this->events.insert({ event.type, event });
				break;
			case sf::Event::MouseMoved:
			case sf::Event::MouseEntered:
			case sf::Event::MouseLeft:
			case sf::Event::LostFocus:
			case sf::Event::GainedFocus:
				break;
			default:
					this->events.insert({ event.type, event });
				break;
			}
		} else if (consoleManager->checkConsole()) {
			//Console Input Commands
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				LogManager::Instance()->info("Window closed.");
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					consoleManager->hideConsole();
					break;
				case sf::Keyboard::Tilde:
					consoleManager->hideConsole();
					break;
				case sf::Keyboard::Return:
					consoleManager->runCommand();
					break;
				case sf::Keyboard::Up:
					consoleManager->traverseUpHistory();
					break;
				case sf::Keyboard::Down:
					consoleManager->traverseDownHistory();
					break;
				default:
					break;
				}
				break;
			case sf::Event::TextEntered:
				consoleManager->addToInput(event.text.unicode);
				break;
			default:
				break;
			}
		}
		this->publishInputEvent(event);
	}
}


void InputManager::publishInputEvent(const sf::Event& event) {
	std::string key;
	if (event.type == sf::Event::KeyPressed) {
		key = SfEventStringMap::KEY_TO_STRING.at(event.key.code);
	} else {
		key = SfEventStringMap::EVENT_TYPE_TO_STRING.at(event.type);
	}
	MessageManager::Instance()->publish(key);
	const GlobalId subscriptionId = MessagesComponentSystem::Instance()->registerMessageSubscription(key);
	EventsComponentSystem::Instance()->publish(Message(subscriptionId));

}
