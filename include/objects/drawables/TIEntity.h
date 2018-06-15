#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "../GlobalId.h"
#include "../SceneNode.h"

namespace TIE {

class TIEntity : public SceneNode {
	public:
		TIEntity();
		virtual ~TIEntity();

		GlobalId getId() const;

		void setCollidable(bool b);
		bool getCollidable();
void setSprite(const sf::Sprite& sprite);
		const sf::Sprite& getSprite() const;

		virtual void setAngle(float angle);
		virtual float getAngle();

		virtual void setSpeed(float speed);
		virtual float getSpeed();

		virtual void move(const float delta);

		void operator=(const TIEntity&);
		bool operator==(const TIEntity& rhs) const;
		bool operator!=(const TIEntity& rhs) const;
	
	protected:
		sf::Sprite sprite;
		GlobalId id;
		bool collidable = true;

		float speed = 1;

	private:
		virtual void drawSelf(sf::RenderWindow&, sf::RenderStates) const;
		virtual void updateSelf(const float);
};

}
#endif
