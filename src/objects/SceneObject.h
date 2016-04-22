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
	
			virtual void receiveMessage(const Message& msg) const;
			virtual void update();

			void setDraw(bool b);

			const sf::Sprite& getSprite() const;
			GlobalId getId() const;
			bool getDraw();

			void operator=(const SceneObject&);
			bool operator==(const SceneObject& rhs) const;
			bool operator!=(const SceneObject& rhs) const;
		
		protected:
			sf::Sprite sprite;
			sf::Clock& clock;
			GlobalId id;
			bool draw = true;
	};

}

#endif
