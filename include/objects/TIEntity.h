#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <SFML/Graphics.hpp>

#include "Message.h"
#include "GlobalId.h"

namespace TIE
{

	class Message;

	class TIEntity
	{
		public:
			TIEntity();
			virtual ~TIEntity();
	
			virtual void receiveMessage(const Message& msg) const;
			virtual void update();

			void setDraw(bool b);
			void setDrawOrder(int i);
			int getDrawOrder();

			const sf::Sprite& getSprite() const;
			GlobalId getId() const;
			bool getDraw() const;

			void operator=(const TIEntity&);
			bool operator==(const TIEntity& rhs) const;
			bool operator!=(const TIEntity& rhs) const;
		
		protected:
			sf::Sprite sprite;
			sf::Clock& clock;
			GlobalId id;
			bool draw = true;
			int drawOrder = 0;

	};

}

#endif
