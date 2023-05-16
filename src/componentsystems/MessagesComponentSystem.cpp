#include "componentsystems/MessagesComponentSystem.h" 

#include "componentsystems/BehavesComponentSystem.h"
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
	ComponentSystems::insertComponentPropertyIntoMap(MessagesComponentSystem::SUBSCRIPTIONS, this->componentPropertyMap);
}


void MessagesComponentSystem::update(const float delta) {
	std::swap(this->currentFrameMessages, this->nextFrameMessages);
	for (auto& [reciepentId, subscriptions] : this->currentFrameMessages) {
		TIEntity* receipent = WorldManager::Instance()->getTIEntityById(reciepentId);
		for (auto& [subscriptionId, messages] : subscriptions) {
			BehavesComponentSystem::Instance()->onMessage(*receipent, messages);
		}
	}
	this->currentFrameMessages.clear();
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


void MessagesComponentSystem::sendMessage(const GlobalId subscription, const GlobalId sender, const GlobalId reciepent, sol::object payload) {
	if (!this->nextFrameMessages.count(reciepent)) {
        this->nextFrameMessages[reciepent];
	}
    if (!this->nextFrameMessages[reciepent].count(subscription)) {
        this->nextFrameMessages[reciepent][subscription];
    }
    this->nextFrameMessages[reciepent][subscription].push_back({ subscription, sender, payload });
}
