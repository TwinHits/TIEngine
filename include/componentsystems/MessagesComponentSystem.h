#ifndef MESSAGESCOMPONENTSYSTEM_H
#define MESSAGESCOMPONENTSYSTEM_H

#include "componentSystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <vector>
#include <string>

#include "objects/Message.h"
#include "objects/components/MessagesComponent.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class MessagesComponentSystem : public Singleton<MessagesComponentSystem>, public OwnsComponent<MessagesComponent> {
	public:
		MessagesComponentSystem();
		void update(const float);
		MessagesComponent& addComponent(TIEntity&);
		MessagesComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);
		
		const GlobalId registerMessageSubscription(const std::string&);
		const std::map<std::string, GlobalId>& getMessageSubscriptions();

		void subscribe(TIEntity&, GlobalId, std::function<void(Message&)>);

		void sendMessage(const Message&);

		static const inline std::string MESSAGES = "messages";
	private:
		struct Components {
			MessagesComponent& messagesComponent;
		};
		std::list<Components> components;

		std::map<std::string, GlobalId> messageSubscriptions;
		std::map<GlobalId, std::map<GlobalId, std::vector<Message>>> currentFrameMessages;
		std::map<GlobalId, std::map<GlobalId, std::vector<Message>>> nextFrameMessages;

		const GlobalId getSenderId(const GlobalId);
		const GlobalId getRecipientId(const GlobalId);
};

}
#endif
