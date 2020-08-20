#ifndef SHAPECOMPONENTSYSTEM_H
#define SHAPECOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include "objects/components/ShapeComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"

namespace TIE {

class ShapeComponentSystem : public Singleton<ShapeComponentSystem>, ComponentSystem {
	public:
		ShapeComponentSystem() {};
		void update(const float);
		ShapeComponent& addComponent(TIEntity&);
		void addComponent(const TIEntityFactory&, TIEntity&);

	private: 
};

}
#endif 
