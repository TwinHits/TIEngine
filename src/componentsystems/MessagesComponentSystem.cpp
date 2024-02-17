#include "componentsystems/MessagesComponentSystem.h" 

#include "managers/HashManager.h"
#include "managers/LogManager.h"
#include "managers/WorldManager.h"
#include "objects/Message.h"
#include "objects/components/MessagesComponent.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "objects/tientities/TIEntity.h"
#include "utils/ComponentSystems.h"
#include "utils/types/ComponentSystemsTypes.h"

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
                                if (message.valid) {
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


const GlobalId MessagesComponentSystem::registerMessageSubscription(const std::string& name) {
	const GlobalId subscription = HashManager::Instance()->getNewGlobalId();
	if (!this->messageSubscriptions[name]) {
		this->messageSubscriptions[name] = subscription;
		return subscription;
	} else {
		LogManager::Instance()->error("Message subscription with name " + name + " already exists.");
		return 0;
	}
}

const std::map<std::string, GlobalId>& MessagesComponentSystem::getMessageSubscriptions() {
	return this->messageSubscriptions;
}


void MessagesComponentSystem::subscribe(TIEntity& tientity, GlobalId subscription, std::function<void(Message&)> onMessage) {
	MessagesComponent& messagesComponent = this->addComponent(tientity);
	messagesComponent.subscribe(subscription, onMessage);
}


void MessagesComponentSystem::sendMessage(const GlobalId subscription, TIEntity& sender, const GlobalId recipientId) {
	this->sendMessage(subscription, sender, recipientId, sol::nil);
}


void MessagesComponentSystem::sendMessage(const GlobalId subscription, TIEntity& sender, const GlobalId recipientId, sol::object payload) {
	const GlobalId senderId = this->getSenderId(sender);
	const GlobalId redirectedReciepentId = this->getReciepentId(recipientId);
	if (!this->nextFrameMessages.count(redirectedReciepentId)) {
        this->nextFrameMessages[redirectedReciepentId];
	}
    if (!this->nextFrameMessages[redirectedReciepentId].count(subscription)) {
        this->nextFrameMessages[redirectedReciepentId][subscription];
    }
    this->nextFrameMessages[redirectedReciepentId][subscription].push_back({ subscription, senderId, payload });
}


const GlobalId MessagesComponentSystem::getSenderId(TIEntity& tientity) {
	MessagesComponent& messagesComponent = this->addComponent(tientity);
	if (messagesComponent.redirectFromId) {
		return messagesComponent.redirectFromId;
	} else {
		return tientity.getId();
	}
}

const GlobalId MessagesComponentSystem::getReciepentId(const GlobalId recipientId) {
	TIEntity* recipient = WorldManager::Instance()->getTIEntityById(recipientId);
	if (recipient) {
		MessagesComponent& messagesComponent = this->addComponent(*recipient);
		if (messagesComponent.redirectToId) {
			return messagesComponent.redirectToId;
		}
	}
	return recipientId;
}
