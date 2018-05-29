#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <SFML/Graphics.hpp>

#include "../Message.h"
#include "../GlobalId.h"

namespace TIE {

class Message;

class TIEntity {
	public:
		TIEntity();
		virtual ~TIEntity();

		GlobalId getId() const;

		void setDraw(bool b);
		bool getDraw() const;

		void setCollidable(bool b);
		bool getCollidable();

		void setDrawOrder(int i);
		int getDrawOrder() const;

		void setSprite(const sf::Sprite& sprite);
		const sf::Sprite& getSprite() const;

		virtual void setAngle(float angle);
		virtual float getAngle();

		virtual void setSpeed(float speed);
		virtual float getSpeed();

		virtual void update();
		virtual void receiveMessage(const Message& msg) const;

		virtual void move(const float delta);

		void operator=(const TIEntity&);
		bool operator==(const TIEntity& rhs) const;
		bool operator!=(const TIEntity& rhs) const;
	
	protected:
		sf::Sprite sprite;
		sf::Clock& clock;
		GlobalId id;
		bool draw = true;
		bool collidable = true;
		int drawOrder = 0;

		float speed = 1;
};

}
#endif
