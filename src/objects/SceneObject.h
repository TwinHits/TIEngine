#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <SFML/Graphics.hpp>

#include "../objects/Message.h"

class Message;

class SceneObject
{
	public:
		virtual void receiveMessage(const Message& msg);// = 0;
		virtual void update();// = 0;

		void setDraw(bool b);

		const sf::Sprite& getSprite() const;
		unsigned long getId() const;
		bool getDraw();

		SceneObject(unsigned long id);
		virtual ~SceneObject();

		void operator=(const SceneObject&);
		bool operator==(const SceneObject& rhs) const;
		bool operator!=(const SceneObject& rhs) const;
		
	private:
		sf::Sprite sprite;
		sf::Clock clock;
		unsigned long id;
		bool draw = true;
};

#endif
