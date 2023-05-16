#ifndef LINECOMPONENTSYSTEM_H
#define LINECOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <sol/sol.hpp>

#include "objects/components/LineComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/tientities/TIEntity.h"
#include "objects/factories/tientities/TIEntityFactory.h"

namespace TIE {

class LineComponentSystem : public Singleton<LineComponentSystem>, public OwnsComponent<LineComponent> {
	public:
		LineComponentSystem();
		void update(const float);
		LineComponent& addComponent(TIEntity&);
		LineComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);
		
		void setComponentProperty(const std::string&, float, TIEntity&);
		sol::object getComponentProperty(const std::string&, TIEntity&);
			
		void setLine(TIEntity&);
		void setLine(LineComponent&, TIEntity&);
		void setLine(LineComponent&, PositionComponent&);

		std::pair<GlobalId, GlobalId> addWireframe(TIEntity& tientity);

		const static inline std::string LINE = "line";
		const static inline std::string MAGNITUDE = "line.magnitude";

	private:        
		struct Components {
			LineComponent& lineComponent;
			PositionComponent& positionComponent;
		};
		std::list<Components> components;
};

}
#endif
