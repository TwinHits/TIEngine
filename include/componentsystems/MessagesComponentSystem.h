#ifndef MESSAGESCOMPONENTSYSTEM_H
#define MESSAGESCOMPONENTSYSTEM_H

#include "componentSystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <vector>
#include <string>

#include "objects/Message.h"
#include "objects/components/MessagesComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class MessagesComponentSystem : public Singleton<MessagesComponentSystem>, public OwnsComponent<MessagesComponent> {
	public:
		MessagesComponentSystem();
		void update(const float);
		MessagesComponent& addComponent(TIEntity&);
		MessagesComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);
		
		const GlobalId registerMessageSubscription();

		void sendMessage(const GlobalId, const GlobalId, const GlobalId, sol::object);

		bool hasMessages(TIEntity&);
		bool hasMessages(TIEntity&, GlobalId);
		const std::vector<Message>& getMessages(TIEntity&, GlobalId);

		static const inline std::string MESSAGES = "messages";
		static const inline std::string SUBSCRIPTIONS = "messages.subscriptions";
	private:
		struct Components {
			MessagesComponent& messagesComponent;
		};
		std::list<Components> components;

		std::map<GlobalId, std::map<GlobalId, std::vector<Message>>> currentFrameMessages;
		std::map<GlobalId, std::map<GlobalId, std::vector<Message>>> nextFrameMessages;
		const std::vector<Message> emptyMessages; // For passing a reference to an empty vector
};

}
#endif
