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
#include "utils/types/ComponentSystemsTypes.h"

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
		bool setComponentProperty(const std::string&, const sf::Vector2f&, TIEntity&);
		bool setComponentProperty(const std::string&, const sf::Vector2i&, TIEntity&);
		sol::object getComponentProperty(const std::string&, TIEntity&);
		ComponentSystems::ComponentSystemPropertiesMap& populateComponentSystemsPropertiesMap(ComponentSystems::ComponentSystemPropertiesMap&);

		void setTargetPosition(TIEntity&, const sf::Vector2f&);
		void setTargetPosition(TIEntity&, float);

		bool atTargetPosition(TIEntity&);

		static const inline std::string MOVES = "moves";
		static const inline std::string SPEED = "moves.speed";
		static const inline std::string ACCELERATION = "moves.acceleration";
		static const inline std::string DECELERATION = "moves.deceleration";

		static const inline std::string ROTATES = "moves.rotates";
		static const inline std::string ROTATION = "moves.rotation";
		static const inline std::string ROTATIONAL_SPEED = "moves.rotationalSpeed";
		static const inline std::string ROTATIONAL_ACCELERATION = "moves.rotationalAcceleration";

		static const inline std::string DESTINATION = "moves.destination";
		static const inline std::string AT_DESTINATION = "moves.atDestination";
		static const inline std::string TARGET_ROTATION = "moves.targetRotation";
	private:
		struct Components {
			MovesComponent& movesComponent;
			PositionComponent& positionComponent;
		};
		std::list<Components> components;

		void setTargetRotation(MovesComponent&, PositionComponent&);

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
