#ifndef MOVESCOMPONENTSYSTEM_H
#define MOVESCOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <string>

#include "objects/components/MovesComponent.h"
#include "objects/components/PositionComponent.h"

namespace TIE {

class MovesComponentSystem : public Singleton<MovesComponentSystem>, public OwnsComponent<MovesComponent> {
	public:
		MovesComponentSystem();
		void update(const float);
		MovesComponent& addComponent(TIEntity&);
		MovesComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);
		
		void setComponentProperty(const std::string&, float, TIEntity&);
		void setComponentProperty(const std::string&, const sf::Vector2f&, TIEntity&);
		void setComponentProperty(const std::string&, const sf::Vector2i&, TIEntity&);
		void setComponentProperty(const std::string&, const std::vector<sf::Vector2f>&, TIEntity&);
		sol::object getComponentProperty(const std::string&, TIEntity&);

		void setTargetPosition(TIEntity&, float);
		void setTargetPosition(TIEntity&, const sf::Vector2f&);
		void setTargetPosition(MovesComponent&, PositionComponent&, const sf::Vector2f&, TIEntity&);

		bool atTargetPosition(TIEntity&);
		bool atTargetPosition(MovesComponent&, PositionComponent&);

		void setTargetRotation(MovesComponent&, PositionComponent&, TIEntity&);

		bool atTargetRotation(TIEntity&);
		bool atTargetRotation(MovesComponent&, PositionComponent&);

		std::pair<GlobalId, GlobalId> addWireframe(TIEntity&);

		static const inline std::string MOVES = "moves";
		static const inline std::string STRATEGY = "strategy";
		static const inline std::string SPEED = "moves_speed";
		static const inline std::string ACCELERATION = "acceleration";

		static const inline std::string ROTATES = "moves_rotates";
		static const inline std::string ROTATIONAL_SPEED = "rotationalSpeed";
		static const inline std::string ROTATIONAL_ACCELERATION = "rotationalAcceleration";

		static const inline std::string DESTINATION = "destination";
		static const inline std::string DESTINATION_PATH = "destination_path";
		static const inline std::string DESTINATION_X = "destination_x";
		static const inline std::string DESTINATION_Y = "destination_y";
		static const inline std::string AT_DESTINATION = "atDestination";
		static const inline std::string TARGET_ROTATION = "targetRotation";
		static const inline std::string AT_ROTATION = "atRotation";
	private:
		struct Components {
			MovesComponent& movesComponent;
			PositionComponent& positionComponent;
			TIEntity& tientity;
		};
		std::list<Components> components;

		GlobalId atDestinationMessageSubscription = 0;

		void assignMovesStrategyByName(MovesComponent&, const std::string&);

		void setTargetRotationDirection(MovesComponent&, PositionComponent&);

		bool atTargetSpeed(MovesComponent&);

		void accelerate(MovesComponent&, PositionComponent&, const float);
		void accelerateRotation(MovesComponent&, PositionComponent&, const float);
		void rotate(MovesComponent&, PositionComponent&, const float);
		void move(MovesComponent&, PositionComponent&, const float);
};

}
#endif
