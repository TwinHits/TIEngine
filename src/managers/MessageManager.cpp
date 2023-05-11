#include "managers/MessageManager.h"

#include "managers/HashManager.h"
#include "objects/GlobalId.h"

using namespace TIE;

bool MessageManager::initialize() {
	return true;
}


void MessageManager::subscribe(const std::string& subscription, std::function<void()> onMessage) {
	if (!this->subscriptions.count(subscription)) {
		this->subscriptions[subscription];
	}
	this->subscriptions[subscription].push_back(onMessage);
}


void MessageManager::sendMessage(const std::string& subscription) {
	if (this->subscriptions.count(subscription)) {
		for (auto& onMessage : this->subscriptions[subscription]) {
			onMessage();
		}
	}
}
