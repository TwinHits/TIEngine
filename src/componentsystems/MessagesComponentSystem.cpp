#include "componentsystems/MessagesComponentSystem.h" 

#include "managers/WorldManager.h"

using namespace TIE;

MessagesComponentSystem::MessagesComponentSystem() {
	this->setName(MessagesComponentSystem::MESSAGES);
}


void MessagesComponentSystem::update(const float delta) {
	// Get the next set of messages
	this->currentFrameMessages.clear();
	std::swap(this->currentFrameMessages, this->nextFrameMessages);
	// For each recipient, get the subscriptions with messages sent to them
	for (auto& [recipientId, subscriptions] : this->currentFrameMessages) {
		TIEntity* recipient = WorldManager::Instance()->getTIEntityById(recipientId);
		if (recipient) {
			MessagesComponent* messagesComponent = recipient->getComponent<MessagesComponent>();
			if (messagesComponent) {
				// For each subscription with messages sent to this recipient
                for (auto& [subscriptionId, messages] : subscriptions) {
					// If the recipient cares about this subscription
					if (messagesComponent->subscriptions.count(subscriptionId)) {
						// For each message for this subscription
						for (auto& message : messages) {
                            // For each of the recipient's subscribed onMessage callback
                            for (auto& onMessage : messagesComponent->subscriptions[subscriptionId]) {
								// If the message is still valid
                                if (message->valid) {
                                    onMessage(message);
								} else {
									break;
								}
                            }
                        }
					}
                }
			}
		}
	}
}


MessagesComponent& MessagesComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<MessagesComponent>()) {
        MessagesComponent& messagesComponent = tientity.addComponent<MessagesComponent>();
        this->components.push_back({ messagesComponent });
        return messagesComponent;
	} else {
		return *tientity.getComponent<MessagesComponent>();
	}
}


MessagesComponent& MessagesComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
    MessagesComponent& component = this->addComponent(tientity);
	return component;
}


bool MessagesComponentSystem::removeComponent(TIEntity& tientity) {
	MessagesComponent* messagesComponent = tientity.getComponent<MessagesComponent>();
	if (messagesComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->messagesComponent == messagesComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<MessagesComponent>();
	} else {
		return false;
	}
}


void MessagesComponentSystem::subscribe(TIEntity& tientity, GlobalId subscription, std::function<void(std::shared_ptr<Message>)> onMessage) {
	MessagesComponent& messagesComponent = this->addComponent(tientity);
	messagesComponent.subscribe(subscription, onMessage);
}


void MessagesComponentSystem::sendMessage(Message& message) {
	message.senderId = this->getSenderId(message.senderId);
	const GlobalId redirectedRecipientId = this->getRecipientId(message.recipientId);
	if (!this->nextFrameMessages.count(redirectedRecipientId)) {
        this->nextFrameMessages[redirectedRecipientId];
	}
    if (!this->nextFrameMessages[redirectedRecipientId].count(message.subscription)) {
        this->nextFrameMessages[redirectedRecipientId][message.subscription];
    }
    this->nextFrameMessages[redirectedRecipientId][message.subscription].push_back(std::make_shared<Message>(message));
}


const GlobalId MessagesComponentSystem::getSenderId(const GlobalId senderId) {
	TIEntity* sender = WorldManager::Instance()->getTIEntityById(senderId);
	if (sender) {
		MessagesComponent& messagesComponent = this->addComponent(*sender);
		if (messagesComponent.redirectFromId) {
			return messagesComponent.redirectFromId;
		}
	}
	return senderId;
}


const GlobalId MessagesComponentSystem::getRecipientId(const GlobalId recipientId) {
	TIEntity* recipient = WorldManager::Instance()->getTIEntityById(recipientId);
	if (recipient) {
		MessagesComponent& messagesComponent = this->addComponent(*recipient);
		if (messagesComponent.redirectToId) {
			return messagesComponent.redirectToId;
		}
	}
	return recipientId;
}
