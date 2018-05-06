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

		void setDrawOrder(int i);
		int getDrawOrder() const;

		void setSprite(const sf::Sprite& sprite);
		const sf::Sprite& getSprite() const;

		void setSpeed(double speed);
		double getSpeed() const;

		virtual void update();
		virtual void receiveMessage(const Message& msg) const;

		virtual void move(const sf::Vector2f destination, const float delta);

		void operator=(const TIEntity&);
		bool operator==(const TIEntity& rhs) const;
		bool operator!=(const TIEntity& rhs) const;
	
	protected:
		sf::Sprite sprite;
		sf::Clock& clock;
		GlobalId id;
		bool draw = true;
		int drawOrder = 0;

		double speed = 1;
};

}
#endif
