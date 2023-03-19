#include "componentsystems/MessagesComponentSystem.h" 

#include "managers/HashManager.h"
#include "objects/Message.h"
#include "objects/components/MessagesComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/tientities/TIEntity.h"
#include "utils/ComponentSystems.h"
#include "utils/types/ComponentSystemsTypes.h"

using namespace TIE;

MessagesComponentSystem::MessagesComponentSystem() {
	this->setName(MessagesComponentSystem::MESSAGES);
	ComponentSystems::insertComponentPropertyIntoMap(MessagesComponentSystem::SUBSCRIPTIONS, this->componentPropertyMap);
}


void MessagesComponentSystem::update(const float delta) {
	for (auto& [subscriptionId, messageQueue] : this->currentFrameMessages) {
		messageQueue.clear();
	}
	std::swap(this->currentFrameMessages, this->nextFrameMessages);
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


bool MessagesComponentSystem::setComponentProperty(const std::string& key, bool value, TIEntity& tientity) {
    MessagesComponent* component = tientity.getComponent<MessagesComponent>();
	if (component != nullptr) {
	}
    return false;
}


bool MessagesComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity)  {
    MessagesComponent* component = tientity.getComponent<MessagesComponent>();
	if (component != nullptr) {
	}
	return true;
}


bool MessagesComponentSystem::setComponentProperty(const std::string& key, const sf::Vector2f& value, TIEntity& tientity)  {
	MessagesComponent* component = tientity.getComponent<MessagesComponent>();
	if (component != nullptr) {
	}
	return false;
}


bool MessagesComponentSystem::setComponentProperty(const std::string& key, const sf::Vector2i& value, TIEntity& tientity) {
	MessagesComponent* component = tientity.getComponent<MessagesComponent>();
	if (component != nullptr) {
	}
	return false;
}


sol::object MessagesComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
	MessagesComponent* component = tientity.getComponent<MessagesComponent>();
	if (component != nullptr) {
	}
	return ScriptManager::Instance()->getObjectFromValue(nullptr);
}


const GlobalId MessagesComponentSystem::registerMessageSubscription() {
	const GlobalId subscription = HashManager::Instance()->getNewGlobalId();
	this->currentFrameMessages[subscription];
	this->nextFrameMessages[subscription];
	return subscription;
}


void MessagesComponentSystem::sendMessage(const GlobalId subscription, const GlobalId sender, const GlobalId reciever, sol::object payload) {
	if (this->nextFrameMessages.count(subscription)) {
		if (!this->nextFrameMessages[subscription].count(reciever)) {
			this->nextFrameMessages[subscription][reciever];
		}
		this->nextFrameMessages[subscription][reciever].push_back({ subscription, sender, payload });
	}
}


bool MessagesComponentSystem::hasMessages(TIEntity& tientity) {
	MessagesComponent* messagesComponent = tientity.getComponent<MessagesComponent>();
	if (messagesComponent) {
		for (auto subscription : messagesComponent->subscriptions) {
			if (this->hasMessages(tientity, subscription)) {
				return true;
			}
		}
	}
	return false;
}


bool MessagesComponentSystem::hasMessages(TIEntity& tientity, GlobalId subscription) {
	if (this->currentFrameMessages.count(subscription)) {
		return this->currentFrameMessages.at(subscription).count(tientity.getId());
	}
	return false;
}


const std::vector<Message>& MessagesComponentSystem::getMessages(TIEntity& tientity, GlobalId subscription) {
	if (this->currentFrameMessages.count(subscription)) {
		if (this->currentFrameMessages.at(subscription).count(tientity.getId())) {
			return this->currentFrameMessages.at(subscription).at(tientity.getId());
		}
	}
	return this->emptyMessages;
}
