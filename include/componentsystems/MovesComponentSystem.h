#ifndef MOVESCOMPONENTSYSTEM_H
#define MOVESCOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/MovesComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"
#include "objects/enumeration/Direction.h"

namespace TIE {

class MovesComponentSystem : public Singleton<MovesComponentSystem>, ComponentSystem {
	public:
		MovesComponentSystem() {};
		void update(const float);

		void addComponent(const TIEntityFactory&, TIEntity&);
		
		void setTargetPosition(MovesComponent&, PositionComponent&, Direction);
		void setTargetPosition(MovesComponent&, PositionComponent&, sf::Vector2f&);

		static const std::string MOVES;
		static const std::string MAXSPEED;
		static const std::string ACCELERATION;
		static const std::string DIRECTION;
		static const std::string ROTATIONSPEED;
	private:
		struct Components {
			MovesComponent& movesComponent;
			PositionComponent& positionComponent;
		};
		std::vector<Components> components;

		virtual void move(MovesComponent&, PositionComponent&, const float);
		virtual void rotate(MovesComponent&, PositionComponent&, const float);
		virtual void accelerate(MovesComponent&, const float);

		bool arePositionsCloseEnough(const sf::Vector2f&, const sf::Vector2f&);
		bool areRotationsCloseEnough(const float, const float);
		bool areFloatsCloseEnough(const float, const float);

		static const float CLOSE_ENOUGH;
};

}
#endif
