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

class MovesComponentSystem : public Singleton<MovesComponentSystem>, public ComponentSystem {
	public:
		MovesComponentSystem() {};
		void update(const float);
		void addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);
		const std::string& getName();
		
		void setTargetPosition(TIEntity&, Direction);
		void setTargetPosition(TIEntity&, sf::Vector2f&);
		bool atTargetPosition(TIEntity&);

		static const inline std::string MOVES = "moves";
		static const inline std::string MAXSPEED = "moves.maxSpeed";
		static const inline std::string ACCELERATION = "moves.acceleration";
		static const inline std::string ROTATIONSPEED = "moves.rotationSpeed";
	private:
		struct Components {
			MovesComponent& movesComponent;
			PositionComponent& positionComponent;
		};
		std::list<Components> components;

		virtual void move(MovesComponent&, PositionComponent&, const float);
		virtual void rotate(MovesComponent&, PositionComponent&, const float);
		virtual void accelerate(MovesComponent&, const float);
};

}
#endif
