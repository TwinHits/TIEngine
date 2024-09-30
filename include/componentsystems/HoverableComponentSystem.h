#ifndef HOVERABLECOMPONENTSYSTEM_H
#define HOVERABLECOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <vector>

#include "objects/components/HoverableComponent.h"

namespace TIE {

	class HoverableComponentSystem : public Singleton<HoverableComponentSystem>, public OwnsComponent<HoverableComponent> {
	public:
		HoverableComponentSystem();
		void update(const float);
		HoverableComponent& addComponent(const TIEntityFactory&, TIEntity&);
		HoverableComponent& addComponent(TIEntity&);
		bool removeComponent(TIEntity&);

		void setOnHover(TIEntity&, std::function<void(Message&)>);
		void setOnHover(TIEntity&, const GlobalId onHoverFunctonId);

		const std::vector<std::reference_wrapper<TIEntity>>& getHoveredTIEntities();

		static const inline std::string HOVERABLE = "hoverable";
		static const inline std::string ON_HOVER = "onHover";

	private:
		void onHover();

		GlobalId hoveredMessageSubscription = 0;

		std::vector<std::reference_wrapper<TIEntity>> cache;

		struct Components {
			HoverableComponent& hoverableComponent;
			TIEntity& tientity;
		};
		std::list<Components> components;

	};

}
#endif
