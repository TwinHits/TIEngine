#ifndef MOVESCOMPONENTSYSTEM_H
#define MOVESCOMPONENTSYSTEM_H

#include "ComponentSystem.h"

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/MovesComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"

namespace TIE {

class MovesComponentSystem : public ComponentSystem {
	public:
		MovesComponentSystem() {};
		
		void update(TIEntity&, const float);

		static MovesComponent* addMovesComponent(const TIEntityFactory&, TIEntity&);

		static const std::string MOVES;
		static const std::string SPEED;
		static const std::string DIRECTION;

	private:
		virtual void move(MovesComponent*, SpriteComponent*, const float);

};

}
#endif
