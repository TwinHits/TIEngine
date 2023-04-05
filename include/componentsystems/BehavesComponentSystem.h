#ifndef BEHAVESCOMPONENTSYSTEM_H
#define BEHAVESCOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <string>
#include <vector>

#include "objects/components/BehavesComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class BehavesComponentSystem : public Singleton<BehavesComponentSystem>, public OwnsComponent<BehavesComponent> {
	public:
		BehavesComponentSystem();
		void update(const float);
		BehavesComponent& addComponent(TIEntity&);
		BehavesComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);
		
		void setComponentProperty(const std::string&, float, TIEntity&);
		sol::object getComponentProperty(const std::string&, TIEntity&);

		void onMessage(TIEntity&, const std::vector<Message>&);

		static const inline std::string BEHAVES = "behaves";
		static const inline std::string ROOT_STATE = "behaves.rootState";
		static const inline std::string ROOT_PAYLOAD = "behaves.rootPayload";
	private:
		struct Components {
			BehavesComponent& behavesComponent;
		};
		std::list<Components> components;
};

}
#endif
