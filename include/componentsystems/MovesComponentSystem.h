#ifndef MOVESCOMPONENTSYSTEM_H
#define MOVESCOMPONENTSYSTEM_H

#include "ComponentSystem.h"

#include <SFML/Graphics.hpp>

#include "objects/components/MovesComponent.h"
#include "objects/components/SpriteComponent.h"

namespace TIE {

class MovesComponentSystem : public ComponentSystem {
	public:
		MovesComponentSystem() {};
		
		void update(TIEntity&, const float);

	private:
		virtual void move(MovesComponent*, SpriteComponent*, const float);

};

}
#endif
