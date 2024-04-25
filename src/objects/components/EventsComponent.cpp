#include "objects/components/EventsComponent.h"

#include "objects/GlobalId.h"
#include "objects/Message.h"

using namespace TIE;

bool EventsComponent::isSubscribedTo(const GlobalId subscriptionId) {
	return this->subscriptions.count(subscriptionId);
}


const std::vector<std::function<void(Message&)>>* EventsComponent::getHandlersFor(const GlobalId subscriptionId) {
	if (this->isSubscribedTo(subscriptionId)) {
		return &this->subscriptions.at(subscriptionId);
	} else {
		return nullptr;
	}
}


void EventsComponent::subscribe(const GlobalId subscriptionId, std::function<void(Message&)> handler) {
	if (!this->isSubscribedTo(subscriptionId)) {
		this->subscriptions[subscriptionId];
	}
	this->subscriptions[subscriptionId].push_back(handler);
}


const GlobalId EventsComponent::redirectsTo() {
	return this->redirectToId;
}


const GlobalId EventsComponent::redirectsFrom() {
	return this->redirectFromId;
}
