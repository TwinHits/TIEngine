#ifndef MOVESCOMPONENTSYSTEM_H
#define MOVESCOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/MovesComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/tientities/TIEntity.h"
#include "objects/enumeration/Direction.h"
#include "utils/types/ComponentSystemsTypes.h"

namespace TIE {

class MovesComponentSystem : public Singleton<MovesComponentSystem>, public OwnsComponent<MovesComponent> {
	public:
		MovesComponentSystem();
		void update(const float);
		MovesComponent& addComponent(TIEntity&);
		MovesComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);
		
		void setComponentProperty(const std::string&, bool, TIEntity&);
		void setComponentProperty(const std::string&, float, TIEntity&);
		void setComponentProperty(const std::string&, const sf::Vector2f&, TIEntity&);
		void setComponentProperty(const std::string&, const sf::Vector2i&, TIEntity&);
		sol::object getComponentProperty(const std::string&, TIEntity&);

		void setTargetPosition(TIEntity&, float);
		void setTargetPosition(TIEntity&, const sf::Vector2f&);
		void setTargetPosition(MovesComponent&, PositionComponent&, const sf::Vector2f&);

		bool atTargetPosition(TIEntity&);
		bool atTargetRotation(TIEntity&);

		static const inline std::string MOVES = "moves";
		static const inline std::string SPEED = "moves.speed";
		static const inline std::string ACCELERATION = "moves.acceleration";
		static const inline std::string DECELERATION = "moves.deceleration";

		static const inline std::string ROTATES = "moves.rotates";
		static const inline std::string ROTATIONAL_SPEED = "moves.rotationalSpeed";
		static const inline std::string ROTATIONAL_ACCELERATION = "moves.rotationalAcceleration";

		static const inline std::string DESTINATION = "moves.destination";
		static const inline std::string DESTINATION_X = "moves.destination.x";
		static const inline std::string DESTINATION_Y = "moves.destination.y";
		static const inline std::string AT_DESTINATION = "moves.atDestination";
		static const inline std::string TARGET_ROTATION = "moves.targetRotation";
		static const inline std::string AT_ROTATION = "moves.atRotation";
	private:
		struct Components {
			MovesComponent& movesComponent;
			PositionComponent& positionComponent;
		};
		std::list<Components> components;

		void setTargetRotation(MovesComponent&, PositionComponent&);
		void setTargetRotationDirection(MovesComponent&, PositionComponent&);

		bool atTargetPosition(MovesComponent&, PositionComponent&);
		bool atTargetSpeed(MovesComponent&);
		bool atTargetRotation(MovesComponent&, PositionComponent&);

		virtual void accelerate(MovesComponent&, PositionComponent&, const float);
		virtual void accelerateRotation(MovesComponent&, PositionComponent&, const float);
		virtual void rotate(MovesComponent&, PositionComponent&, const float);
		virtual void move(MovesComponent&, PositionComponent&, const float);
};

}
#endif
