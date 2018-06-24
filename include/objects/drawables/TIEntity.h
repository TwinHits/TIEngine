#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "../GlobalId.h"
#include "../SceneNode.h"

namespace TIE {

class TIEntity : public SceneNode {
	public:
		TIEntity();
		virtual ~TIEntity();

		void setSprite(const sf::Sprite& sprite);
		const sf::Sprite& getSprite() const;

		void setVelocity(sf::Vector2f); //x = speed, y = direction
		const sf::Vector2f getVelocity();

		virtual void move(const float delta);

		virtual void drawSelf(sf::RenderTarget&, sf::RenderStates) const;
		virtual void updateSelf(const float);

		void operator=(const TIEntity&);
		bool operator==(const TIEntity& rhs) const;
		bool operator!=(const TIEntity& rhs) const;
	
	protected:
		sf::Sprite sprite;
		sf::Vector2f velocity = sf::Vector2f(0,0);

	private:
};

}
#endif
