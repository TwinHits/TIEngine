#ifndef MOVESCOMPONENTSYSTEM_H
#define MOVESCOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <string>

#include "objects/components/MovesComponent.h"
#include "objects/components/PathsComponent.h"
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
		sol::object getComponentProperty(const std::string&, TIEntity&);

		void setTargetRotation(MovesComponent&, PositionComponent&, TIEntity&);
		bool atTargetRotation(TIEntity&);

		static const inline std::string MOVES = "moves";
		static const inline std::string STRATEGY = "strategy";
		static const inline std::string SPEED = "moves_speed";
		static const inline std::string ACCELERATION = "acceleration";

		static const inline std::string ROTATES = "moves_rotates";
		static const inline std::string ROTATIONAL_SPEED = "rotationalSpeed";
		static const inline std::string ROTATIONAL_ACCELERATION = "rotationalAcceleration";

		static const inline std::string TARGET_ROTATION = "targetRotation";
		static const inline std::string AT_ROTATION = "atRotation";
	private:
		struct Components {
			MovesComponent& movesComponent;
			PositionComponent& positionComponent;
			PathsComponent& pathsComponent;
			TIEntity& tientity;
		};
		std::list<Components> components;

		GlobalId atDestinationMessageSubscription = 0;

		void assignMovesStrategyByName(MovesComponent&, const std::string&);
		void setTargetRotationDirection(MovesComponent&, PositionComponent&);
};

}
#endif
