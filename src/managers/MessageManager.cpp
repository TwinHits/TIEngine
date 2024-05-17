#include "managers/MessageManager.h"

#include "managers/HashManager.h"
#include "objects/GlobalId.h"

using namespace TIE;

void MessageManager::subscribe(const std::string& subscription, std::function<void()> onMessage) {
	if (!this->subscriptions.count(subscription)) {
		this->subscriptions[subscription];
	}
	this->subscriptions[subscription].push_back(onMessage);
}


void MessageManager::publish(const std::string& subscription) {
	if (this->subscriptions.count(subscription)) {
		for (auto& onMessage : this->subscriptions[subscription]) {
			onMessage();
		}
	}
}


const GlobalId MessageManager::getSubscriptionId(const std::string& subscription) {
	if (!this->subscriptionIds.count(subscription)) {
		this->subscriptionIds[subscription] = HashManager::Instance()->getNewGlobalId();
	}
	return this->subscriptionIds.at(subscription);
}


const std::map<const std::string, GlobalId>& MessageManager::getSubscriptionIds() {
	return this->subscriptionIds;
}
