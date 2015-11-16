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

		void action(const SceneObject& target);

		SceneObject(unsigned long id);
		~SceneObject();

		void operator=(const SceneObject&);
		bool operator==(const SceneObject& rhs) const;
		bool operator!=(const SceneObject& rhs) const;
		
	private:
		sf::Sprite sprite;
		bool draw = true;
		
		sf::Clock clock;

		unsigned long id;
};

#endif
