#ifndef SELECTABLECOMPONENTSYSTEM_H
#define SELECTABLECOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include "objects/components/SelectableComponent.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

	class SelectableComponentSystem : public Singleton<SelectableComponentSystem>, public OwnsComponent<SelectableComponent> {
	public:
		SelectableComponentSystem();
		void update(const float);
		SelectableComponent& addComponent(const TIEntityFactory&, TIEntity&);
		SelectableComponent& addComponent(TIEntity&);
		bool removeComponent(TIEntity&);

		static const inline std::string SELECTABLE = "selectable";
		static const inline std::string SELECTED = "can_be_selected";

	private:
		struct Components {
			SelectableComponent& selectableComponent;
			TIEntity& tientity;
		};
		std::list<Components> components;
	};

}
#endif
