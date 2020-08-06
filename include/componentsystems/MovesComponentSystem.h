#ifndef MOVESCOMPONENTSYSTEM_H
#define MOVESCOMPONENTSYSTEM_H

#include "ComponentSystem.h"

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/MovesComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"
#include "objects/enumeration/Direction.h"

namespace TIE {

class MovesComponentSystem : public ComponentSystem {
	public:
		MovesComponentSystem() {};
		void update(TIEntity&, const float);

		static MovesComponent* addMovesComponent(const TIEntityFactory&, TIEntity&);
		
		static void setDestination(TIEntity&, Direction);
		static void setDestination(TIEntity&, sf::Vector2f&);

		static const std::string MOVES;
		static const std::string SPEED;
		static const std::string DIRECTION;
		static const std::string SPEED_KEY;
		static const std::string DIRECTION_KEY;
	private:
		virtual void move(MovesComponent&, SpriteComponent&, const float);
		static bool arePositionsCloseEnough(const sf::Vector2f&, const sf::Vector2f&);
		bool recalculateVelocity(MovesComponent& movesComponent);

		static const float CLOSE_ENOUGH;
};

}
#endif
