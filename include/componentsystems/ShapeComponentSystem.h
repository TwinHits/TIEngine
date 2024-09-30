#ifndef SHAPECOMPONENTSYSTEM_H
#define SHAPECOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <string>

#include "objects/components/PositionComponent.h"
#include "objects/components/ShapeComponent.h"

namespace TIE {

class ShapeComponentSystem : public Singleton<ShapeComponentSystem>, public OwnsComponent<ShapeComponent> {
	public:
		ShapeComponentSystem();
		void update(const float);
		ShapeComponent& addComponent(const TIEntityFactory&, TIEntity&);
		ShapeComponent& addComponent(TIEntity&);
		bool removeComponent(TIEntity&);

		static const inline std::string SHAPE = "shape";

	private: 
		struct Components {
			ShapeComponent& shapeComponent;
			PositionComponent& positionComponent;
			TIEntity& tientity;
		};
		std::list<Components> components;
};

}
#endif 
