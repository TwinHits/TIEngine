#ifndef MOVESCOMPONENTSYSTEM_H
#define MOVESCOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/MovesComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"
#include "objects/enumeration/Direction.h"

namespace TIE {

class MovesComponentSystem : public Singleton<MovesComponentSystem>, ComponentSystem {
	public:
		MovesComponentSystem() {};
		void update(TIEntity&, const float);

		MovesComponent* addComponent(const TIEntityFactory&, TIEntity&);
		
		void setTargetPosition(TIEntity&, Direction);
		void setTargetPosition(TIEntity&, sf::Vector2f&);

		static const std::string MOVES;
		static const std::string SPEED;
		static const std::string DIRECTION;
		static const std::string ROTATIONSPEED;
		static const std::string SPEED_KEY;
		static const std::string DIRECTION_KEY;
		static const std::string ROTATIONSPEED_KEY;
	private:
		virtual void move(MovesComponent&, SpriteComponent&, const float);
		virtual void rotate(MovesComponent&, SpriteComponent&, const float);

		static bool arePositionsCloseEnough(const sf::Vector2f&, const sf::Vector2f&);
		static bool areRotationsCloseEnough(const float, const float);
		bool recalculateVelocity(MovesComponent& movesComponent);
		bool recalculateAngularVelocity(MovesComponent& movesComponent);

		static const float CLOSE_ENOUGH;
};

}
#endif
