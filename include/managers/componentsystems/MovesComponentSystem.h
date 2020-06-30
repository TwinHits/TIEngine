#ifndef MOVESCOMPONENTSYSTEM_H
#define MOVESCOMPONENTSYSTEM_H

#include <SFML/Graphics.hpp>

#include "ComponentSystem.h"

namespace TIE {

class MovesComponentSystem : public ComponentSystem {
	public:
		MovesComponentSystem() {};
		
		void execute(TIEntity&);

	private:
		//virtual void move(const float delta);

};

}
#endif
