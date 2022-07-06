#ifndef POSITIONCOMPONENTSYSTEM_H
#define POSITIONCOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/PositionComponent.h"
#include "objects/entities/TIEntity.h"
#include "utils/types/ComponentSystemsTypes.h"

namespace TIE {
class PositionComponentSystem : public Singleton<PositionComponentSystem>, public ComponentSystem {
    public:
		PositionComponentSystem() {};
		void update(const float);
		void addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);
		const std::string& getName();

		bool setComponentProperty(const std::string&, bool, TIEntity&);
		bool setComponentProperty(const std::string&, float, TIEntity&);
		bool setComponentProperty(const std::string&, const sf::Vector2f&, TIEntity&);
		sol::object getComponentProperty(const std::string&, TIEntity&);
		ComponentSystems::ComponentSystemPropertiesMap& populateComponentSystemsPropertiesMap(ComponentSystems::ComponentSystemPropertiesMap&);

		void setPosition(TIEntity&, float, float);

		sf::Vector2f getWorldPosition(TIEntity&);
		float getWorldRotation(TIEntity&);
		sf::Transform getWorldTransform(TIEntity&);

		static const inline std::string POSITION = "position";
		static const inline std::string X = "position.x";
		static const inline std::string Y = "position.y";
		static const inline std::string ROTATION = "position.rotation";
		static const inline std::string WORLD_ROTATION = "position.worldRotation";
		static const inline std::string ROTATES = "position.rotates";
		static const inline std::string POSITION_POSITION = "position.position";
		static const inline std::string WORLD_POSITION = "position.worldPosition";

    private:
		struct Components {
			PositionComponent& positionComponent;
			TIEntity& tientity;
		};
		std::list<Components> components;

};
}

#endif