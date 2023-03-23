#ifndef COLLIDESCOMPONENTSYSTEM_H
#define COLLIDESCOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <set>

#include "objects/components/CollidesComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/tientities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"

namespace TIE {

// Collides
// Sprite

class CollidesComponentSystem : public Singleton<CollidesComponentSystem>, public OwnsComponent<CollidesComponent> {
	public:
		CollidesComponentSystem();
		void update(const float);
		CollidesComponent& addComponent(TIEntity&);
		CollidesComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);

	//	virtual sf::FloatRect getHitBox() const;
		void checkForCollisions();
		
		const static inline std::string COLLIDES = "collides";

	private:        
		struct Components {
			CollidesComponent& collidesComponent;
			SpriteComponent& spriteComponent;
		};
		std::list<Components> components;

		std::set<std::pair<TIEntity*, TIEntity*> > collisions;
};

}
#endif
