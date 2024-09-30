#ifndef COLLISIONBOXFACTORY_H
#define COLLISIONBOXFACTORY_H

#include <SFML/Graphics.hpp>

#include "objects/tientities/TIEntity.h"

namespace TIE {

class CollisionBoxFactory {
    public:
		CollisionBoxFactory(TIEntity*);
		CollisionBoxFactory(TIEntity&);
		CollisionBoxFactory(const CollisionBoxFactory&) {};

		const GlobalId getId();
	
		CollisionBoxFactory& setParent(TIEntity&);

		CollisionBoxFactory& setPosition(const sf::Vector2f&);
		CollisionBoxFactory& setPosition(const float, const float);

		CollisionBoxFactory& setSize(const sf::Vector2f&);
		CollisionBoxFactory& setSize(const float, const float);

		CollisionBoxFactory& setRect(const sf::FloatRect&);
		CollisionBoxFactory& setRect(const float, const float, const float, const float);

		TIEntity& build();

		static const inline std::string COLLISION_BOX = "Collision Box";
    private:
		GlobalId id = 0;
		TIEntity* parent = nullptr;

		sf::Vector2f size;
		sf::Vector2f position;
};

}


#endif