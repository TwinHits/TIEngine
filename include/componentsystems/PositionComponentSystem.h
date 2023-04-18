#ifndef POSITIONCOMPONENTSYSTEM_H
#define POSITIONCOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "objects/components/PositionComponent.h"
#include "objects/tientities/TIEntity.h"
#include "utils/types/ComponentSystemsTypes.h"

namespace TIE {
class PositionComponentSystem : public Singleton<PositionComponentSystem>, public OwnsComponent<PositionComponent> {
    public:
		PositionComponentSystem();
		void update(const float);
		PositionComponent& addComponent(TIEntity&);
		PositionComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);

		void setComponentProperty(const std::string&, float, TIEntity&);
		void setComponentProperty(const std::string&, const sf::Vector2f&, TIEntity&);
		sol::object getComponentProperty(const std::string&, TIEntity&);

		void setPosition(TIEntity&, float, float);

		void updateWorldCoordinates(TIEntity&);
		void updateWorldCoordinates(PositionComponent&, TIEntity&);
		sf::Vector2f getWorldPosition(TIEntity&);
		float getWorldRotation(TIEntity&);
		sf::Transform getWorldTransform(TIEntity&);

		static bool arePositionsInRange(PositionComponent&, PositionComponent&, const float);

		static std::vector<TIEntity*> findTIEntitiesWithinRange(TIEntity&, const float, TIEntity&);

		static const inline std::string POSITION = "position";
		static const inline std::string ROTATION = "position.rotation";
		static const inline std::string WORLD_ROTATION = "position.worldRotation";
		static const inline std::string ROTATES = "position.rotates";
		static const inline std::string POSITION_POSITION = "position.position";
		static const inline std::string POSITION_X = "position.x";
		static const inline std::string POSITION_Y = "position.y";
		static const inline std::string WORLD_POSITION = "position.worldPosition";

    private:
		struct Components {
			PositionComponent& positionComponent;
			TIEntity& tientity;
		};
		std::list<Components> components;

		static std::vector<TIEntity*> findTIEntitiesWithinRange(TIEntity&, const float, TIEntity&, std::vector<TIEntity*>&);
};
}

#endif