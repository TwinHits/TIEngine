#ifndef SHAPECOMPONENTSYSTEM_H
#define SHAPECOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include "objects/components/PositionComponent.h"
#include "objects/components/ShapeComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"

namespace TIE {

class ShapeComponentSystem : public Singleton<ShapeComponentSystem>, public ComponentSystem {
	public:
		ShapeComponentSystem() {};
		void update(const float);
		void addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);
		const std::string& getName();

		static const inline std::string SHAPE = "shape";

	private: 
		struct Components {
			ShapeComponent& shapeComponent;
			PositionComponent& positionComponent;
		};
		std::list<Components> components;
};

}
#endif 
