#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <SFML/Graphics.hpp>

#include "../objects/Message.h"

class Message;

class SceneObject
{
	public:
		void setDraw(bool b);

		const sf::Sprite& getSprite() const;
		unsigned long getId() const;
		bool getDraw();

		void receiveMessage(const Message& msg);
		void update();

		void action();

		SceneObject(unsigned long id);
		SceneObject(const SceneObject&);
		~SceneObject();
		void operator=(const SceneObject&);
		
	private:
		sf::Sprite sprite;
		bool draw = true;
		
		sf::Clock clock;

		unsigned long id;
};

#endif
