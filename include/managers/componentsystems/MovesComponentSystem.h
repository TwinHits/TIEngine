#ifndef MOVESCOMPONENTSYSTEM_H
#define MOVESCOMPONENTSYSTEM_H

#include <SFML/Graphics.hpp>

#include "ComponentSystem.h"

#include "objects/components/MovesComponent.h"
#include "objects/components/SpriteComponent.h"

namespace TIE {

class MovesComponentSystem : public ComponentSystem {
	public:
		MovesComponentSystem() {};
		
		void execute(TIEntity&, const float);

	private:
		virtual void move(MovesComponent*, SpriteComponent*, const float);

};

}
#endif
