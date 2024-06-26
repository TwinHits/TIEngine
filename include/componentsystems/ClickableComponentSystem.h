#ifndef CLICKABLECOMPONENTSYSTEM_H
#define CLICKABLECOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include "objects/components/ClickableComponent.h"
#include "objects/components/MessagesComponent.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

	class ClickableComponentSystem : public Singleton<ClickableComponentSystem>, public OwnsComponent<ClickableComponent> {
	public:
		ClickableComponentSystem();
		void update(const float);
		ClickableComponent& addComponent(const TIEntityFactory&, TIEntity&);
		ClickableComponent& addComponent(TIEntity&);
		bool removeComponent(TIEntity&);

		void setOnClick(TIEntity&, std::function<void(Message&)>);
		void setOnClick(TIEntity&, const GlobalId onClickFunctonId);

		static const inline std::string CLICKABLE = "clickable";
		static const inline std::string ON_CLICK = "onClick";

	private:
		void onClick();

		GlobalId clickedMessageSubscription = 0;

		struct Components {
			ClickableComponent& clickableComponent;
			TIEntity& tientity;
		};
		std::list<Components> components;

	};

}
#endif
