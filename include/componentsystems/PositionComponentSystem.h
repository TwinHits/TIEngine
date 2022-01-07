#ifndef POSITIONCOMPONENTSYSTEM_H
#define POSITIONCOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/PositionComponent.h"
#include "objects/entities/TIEntity.h"

namespace TIE {
class PositionComponentSystem : public Singleton<PositionComponentSystem>, public ComponentSystem {
    public:
		PositionComponentSystem() {};
		void update(const float);
		void addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);
		const std::string& getName();

		sf::Vector2f getWorldPosition(TIEntity&);
		float getWorldRotation(TIEntity&);

		static const inline std::string POSITION = "position";
		static const inline std::string X = "position.x";
		static const inline std::string Y = "position.y";
		static const inline std::string ANGLE = "position.angle";

    private:
		struct Components {
			PositionComponent& positionComponent;
		};
		std::list<Components> components;

		sf::Transform getWorldTransform(TIEntity&);
};
}

#endif