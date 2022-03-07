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
		
		bool setComponentProperty(const std::string&, bool, TIEntity&);
		bool setComponentProperty(const std::string&, float, TIEntity&);
		bool setComponentProperty(const std::string&, const std::string&, TIEntity&);

		void setTargetPosition(TIEntity&, sf::Vector2f&);
		void setTargetPosition(TIEntity&, float);
		void setTargetPosition(TIEntity&, Direction);

		bool atTargetPosition(TIEntity&);

		static const inline std::string MOVES = "moves";
		static const inline std::string SPEED = "moves.speed";
		static const inline std::string ACCELERATION = "moves.acceleration";
		static const inline std::string ROTATES = "moves.rotates";
		static const inline std::string ROTATIONSPEED = "moves.rotationSpeed";
	private:
		struct Components {
			MovesComponent& movesComponent;
			PositionComponent& positionComponent;
		};
		std::list<Components> components;

		bool atTargetPosition(MovesComponent&, PositionComponent&);
		bool atTargetSpeed(MovesComponent&);

		virtual void move(MovesComponent&, PositionComponent&, const float);
		virtual void rotate(MovesComponent&, PositionComponent&, const float);
		virtual void accelerate(MovesComponent&, PositionComponent&, const float);
};

}
#endif
