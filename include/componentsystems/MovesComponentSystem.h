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
		void update(const float);

		void addComponent(const TIEntityFactory&, TIEntity&);
		
		void setTargetPosition(MovesComponent&, SpriteComponent&, Direction);
		void setTargetPosition(MovesComponent&, SpriteComponent&, sf::Vector2f&);

		static const std::string MOVES;
		static const std::string MAXSPEED;
		static const std::string ACCELERATION;
		static const std::string DIRECTION;
		static const std::string ROTATIONSPEED;
		static const std::string MAXSPEED_KEY;
		static const std::string ACCELERATION_KEY;
		static const std::string DIRECTION_KEY;
		static const std::string ROTATIONSPEED_KEY;
	private:
		struct Components {
			MovesComponent& movesComponent;
			SpriteComponent& spriteComponent;
		};
		std::vector<Components> components;

		virtual void move(MovesComponent&, SpriteComponent&, const float);
		virtual void rotate(MovesComponent&, SpriteComponent&, const float);
		virtual void accelerate(MovesComponent&, const float);

		bool arePositionsCloseEnough(const sf::Vector2f&, const sf::Vector2f&);
		bool areRotationsCloseEnough(const float, const float);
		bool areFloatsCloseEnough(const float, const float);

		static const float CLOSE_ENOUGH;
};

}
#endif
