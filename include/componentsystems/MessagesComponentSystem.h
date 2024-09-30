#ifndef MESSAGESCOMPONENTSYSTEM_H
#define MESSAGESCOMPONENTSYSTEM_H

#include "componentSystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <memory>
#include <vector>
#include <string>
#include <map>

#include "objects/components/MessagesComponent.h"

namespace TIE {

class MessagesComponentSystem : public Singleton<MessagesComponentSystem>, public OwnsComponent<MessagesComponent> {
	public:
		MessagesComponentSystem();
		void update(const float);
		MessagesComponent& addComponent(TIEntity&);
		MessagesComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);
		
		void subscribe(TIEntity&, GlobalId, std::function<void(std::shared_ptr<Message>)> onMessage);

		void sendMessage(Message&);

		static const inline std::string MESSAGES = "messages";
	private:
		struct Components {
			MessagesComponent& messagesComponent;
		};
		std::list<Components> components;

		std::map<std::string, GlobalId> messageSubscriptions;
		std::map<GlobalId, std::map<GlobalId, std::vector<std::shared_ptr<Message>>>> currentFrameMessages;
		std::map<GlobalId, std::map<GlobalId, std::vector<std::shared_ptr<Message>>>> nextFrameMessages;

		const GlobalId getSenderId(const GlobalId);
		const GlobalId getRecipientId(const GlobalId);
};

}
#endif
