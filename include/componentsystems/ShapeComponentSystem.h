#ifndef SHAPECOMPONENTSYSTEM_H
#define SHAPECOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include "objects/components/PositionComponent.h"
#include "objects/components/ShapeComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class ShapeComponentSystem : public Singleton<ShapeComponentSystem>, public OwnsComponent<ShapeComponent> {
	public:
		ShapeComponentSystem();
		void update(const float);
		ShapeComponent& addComponent(const TIEntityFactory&, TIEntity&);
		ShapeComponent& addComponent(TIEntity&);
		bool removeComponent(TIEntity&);

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
