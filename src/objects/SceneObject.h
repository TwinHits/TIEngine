#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <SFML/Graphics.hpp>

#include "Message.h"
#include "GlobalId.h"



namespace TIE
{

	class Message;

	class SceneObject
	{
		public:
			SceneObject();
			virtual ~SceneObject();
	
			virtual void receiveMessage(const Message& msg) const;// = 0;
			virtual void update();// = 0;

			void setDraw(bool b) const;

			const sf::Sprite& getSprite() const;
			GlobalId getId() const;
			bool getDraw();

			void operator=(const SceneObject&);
			bool operator==(const SceneObject& rhs) const;
			bool operator!=(const SceneObject& rhs) const;
		
		protected:
			sf::Sprite sprite;
			sf::Clock clock;
			GlobalId id;
			mutable bool draw = true;
	};

}

#endif
