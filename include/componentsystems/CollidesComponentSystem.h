#ifndef COLLIDESCOMPONENTSYSTEM_H
#define COLLIDESCOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <set>

#include "objects/components/CollidesComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"

namespace TIE {

class CollidesComponentSystem : public Singleton<CollidesComponentSystem>, ComponentSystem {
	public:
		CollidesComponentSystem() {};
		void update(TIEntity&, const float);
		CollidesComponent* addComponent(const TIEntityFactory&, TIEntity&);

	//	virtual sf::FloatRect getHitBox() const;
		void checkForCollisions();

	private:
		std::set<std::pair<TIEntity*, TIEntity*> > collisions;
};

}
#endif
