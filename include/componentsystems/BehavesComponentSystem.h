#ifndef BEHAVESCOMPONENTSYSTEM_H
#define BEHAVESCOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <string>

#include "objects/components/BehavesComponent.h"

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

		const std::map<std::string, std::string>& getBehaviorTreeNodeTypes();
		const std::map<std::string, std::string>& getBehaviorTreeDecoratorTypes();
		const std::map<std::string, int>& getBehaviorTreeNodeStatuses();
		const BehaviorTree::NodeStatus getNodeStatusForMessageSubscription(const GlobalId);
		const GlobalId getMessageSubscriptionForNodeStatus(const BehaviorTree::NodeStatus);

		static const inline std::string BEHAVES = "behaves";
		static const inline std::string ROOT_BEHAVIOR_TREE_NODE = "rootBehaviorTreeNode";
		static const inline std::string ROOT_FINITE_STATE_MACHINE = "rootFiniteStateMachine";
		static const inline std::string ROOT_PAYLOAD = "rootPayload";
	private:
		void initializeBehaviorTreeNodeTypes();
		void initializeBehaviorTreeDecoratorTypes();
		void initializeBehaviorTreeNodeStatuses();
		void initializeBehaviorTreeNodeStatusMessageSubscriptions();

		struct Components {
			BehavesComponent& behavesComponent;
		};
		std::list<Components> components;

		std::map<std::string, std::string> behaviorTreeNodeTypes;
		std::map<std::string, std::string> behaviorTreeDecoratorTypes;
		std::map<std::string, int> behaviorTreeNodeStatuses;
		std::map<BehaviorTree::NodeStatus, GlobalId> behaviorTreeNodeStatusToMessageSubscription;
		std::map<GlobalId, BehaviorTree::NodeStatus> messageSubscriptionToBehaviorTreeNodeStatus;

};

}
#endif
