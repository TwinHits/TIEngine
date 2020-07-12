#ifndef COLLIDESCOMPONENTSYSTEM_H
#define COLLIDESCOMPONENTSYSTEM_H

#include "ComponentSystem.h"

#include <set>

#include "objects/entities/TIEntity.h"

namespace TIE {

class CollidesComponentSystem : public ComponentSystem {
	public:
		CollidesComponentSystem() {};
		void execute(TIEntity&, const float);

	//	virtual sf::FloatRect getHitBox() const;
		void checkForCollisions();

	private:
		std::set<std::pair<TIEntity*, TIEntity*> > collisions;
};

}
#endif
