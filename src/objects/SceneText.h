#ifndef SCENETEXT_H
#define SCENETEXT_H

#include <SFML/Graphics.hpp>

#include "Message.h"
#include "GlobalId.h"

namespace TIE
{

	class Message;

	class SceneText
	{
		public:
			SceneText();
			virtual ~SceneText();
	
			virtual void receiveMessage(const Message& msg) const;
			virtual void update();

			void setDraw(bool b);

			const sf::Text& getText() const;
			GlobalId getId() const;
			bool getDraw() const;

			void operator=(const SceneText&);
			bool operator==(const SceneText& rhs) const;
			bool operator!=(const SceneText& rhs) const;
		
		protected:
			sf::Text text;
			sf::Clock& clock;
			GlobalId id;
			bool draw = true;
	};

}

#endif
