#ifndef SHAPECOMPONENTSYSTEM_H
#define SHAPECOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include "objects/components/PositionComponent.h"
#include "objects/components/ShapeComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"

namespace TIE {

class ShapeComponentSystem : public Singleton<ShapeComponentSystem>, public ComponentSystem {
	public:
		ShapeComponentSystem();
		void update(const float);
		bool hasComponent(const TIEntity&);
		ShapeComponent& addComponent(const TIEntityFactory&, TIEntity&);
		ShapeComponent& addComponent(TIEntity&);
		bool removeComponent(TIEntity&);
		const std::string& getName();

		bool setComponentProperty(const std::string&, bool, TIEntity&);
		bool setComponentProperty(const std::string&, float, TIEntity&);
		bool setComponentProperty(const std::string&, const std::string&, TIEntity&);
		sol::object getComponentProperty(const std::string&, TIEntity&);

		void addWireframe(TIEntity&, const SpriteComponent&);
		void addWireframe(TIEntity&, const TextComponent&);

		static const inline std::string SHAPE = "shape";

	private: 
		struct Components {
			ShapeComponent& shapeComponent;
			PositionComponent& positionComponent;
			TIEntity& tientity;
		};
		std::list<Components> components;

		ShapeComponent& createWireframe(TIEntity&, const sf::FloatRect&, const sf::Vector2f&);
};

}
#endif 
