#ifndef COLLIDESCOMPONENTSYSTEM_H
#define COLLIDESCOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <set>

#include "objects/components/CollidesComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"

namespace TIE {

// Collides
// Sprite

class CollidesComponentSystem : public Singleton<CollidesComponentSystem>, public ComponentSystem {
	public:
		CollidesComponentSystem() {};
		void update(const float);
		void addComponent(const TIEntityFactory&, TIEntity&);
		const std::string& getName();

		const static inline std::string COLLIDES = "collides";

	//	virtual sf::FloatRect getHitBox() const;
		void checkForCollisions();

	private:        
		struct Components {
			CollidesComponent& collidesComponent;
			SpriteComponent& spriteComponent;
		};
		std::vector<Components> components;

		std::set<std::pair<TIEntity*, TIEntity*> > collisions;
};

}
#endif
