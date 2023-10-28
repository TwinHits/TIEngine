#ifndef BEHAVESCOMPONENTSYSTEM_H
#define BEHAVESCOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <string>
#include <vector>

#include "objects/components/BehavesComponent.h"
#include "objects/factories/tientities/TIEntityFactory.h"
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

		void addSubscriptions(TIEntity&, const std::vector<GlobalId>&, BehaviorTreeNode&);

		void onMessage(TIEntity&, const Message&);
		void onMessage(TIEntity&, const std::vector<Message>&);

		const std::map<std::string, std::string>& getBehaviorTreeNodeTypes();
		const std::map<std::string, int>& getBehaviorTreeNodeStatuses();

		static const inline std::string BEHAVES = "behaves";
		static const inline std::string ROOT_BEHAVIOR_TREE_NODE = "behaves.rootBehaviorTreeNode";
		static const inline std::string ROOT_FINITE_STATE_MACHINE = "behaves.rootFiniteStateMachine";
		static const inline std::string ROOT_PAYLOAD = "behaves.rootPayload";
	private:
		void initializeBehaviorTreeNodeTypes();
		void initializeBehaviorTreeNodeStatuses();

		struct Components {
			BehavesComponent& behavesComponent;
		};
		std::list<Components> components;

		std::map<std::string, std::string> behaviorTreeNodeTypes;
		std::map<std::string, int> behaviorTreeNodeStatuses;
};

}
#endif
