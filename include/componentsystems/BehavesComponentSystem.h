#ifndef BEHAVESCOMPONENTSYSTEM_H
#define BEHAVESCOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <string>

#include "objects/components/BehavesComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class BehavesComponentSystem : public Singleton<BehavesComponentSystem>, public ComponentSystem {
	public:
		BehavesComponentSystem();
		void update(const float);
		bool hasComponent(const TIEntity& tientity);
		BehavesComponent& addComponent(TIEntity&);
		BehavesComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);
		const std::string& getName();
		
		bool setComponentProperty(const std::string&, bool, TIEntity&);
		bool setComponentProperty(const std::string&, float, TIEntity&);
		bool setComponentProperty(const std::string&, const sf::Vector2f&, TIEntity&);
		bool setComponentProperty(const std::string&, const sf::Vector2i&, TIEntity&);
		sol::object getComponentProperty(const std::string&, TIEntity&);

		static const inline std::string BEHAVES = "behaves";
		static const inline std::string ROOT_STATE = "behaves.rootState";
	private:
		struct Components {
			BehavesComponent& behavesComponent;
		};
		std::list<Components> components;
};

}
#endif
