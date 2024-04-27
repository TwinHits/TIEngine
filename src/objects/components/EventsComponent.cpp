#include "objects/components/EventsComponent.h"

#include "objects/GlobalId.h"
#include "objects/Message.h"

using namespace TIE;

void EventsComponent::subscribe(const GlobalId subscriptionId, std::function<void(Message&)> handler) {
	if (!this->hasHandlersFor(subscriptionId)) {
		this->subscriptionToHandlers[subscriptionId];
	}
	this->subscriptionToHandlers[subscriptionId].push_back(handler);
}


bool EventsComponent::hasHandlersFor(const GlobalId subscriptionId) {
	return this->subscriptionToHandlers.count(subscriptionId);
}


const std::vector<std::function<void(Message&)>>* EventsComponent::getHandlersFor(const GlobalId subscriptionId) {
	if (this->hasHandlersFor(subscriptionId)) {
		return &this->subscriptionToHandlers.at(subscriptionId);
	} else {
		return nullptr;
	}
}


void EventsComponent::subscribe(const GlobalId subscriptionId, const GlobalId functionId) {
	if (!this->hasFunctionIdsFor(subscriptionId)) {
		this->subscriptionToFunctionIds[subscriptionId];
	}
	this->subscriptionToFunctionIds[subscriptionId].push_back(functionId);
}


bool EventsComponent::hasFunctionIdsFor(const GlobalId subscriptionId) {
	return this->subscriptionToFunctionIds.count(subscriptionId);
}


const std::vector<GlobalId>* EventsComponent::getFunctionIdsFor(const GlobalId subscriptionId) {
	if (this->hasFunctionIdsFor(subscriptionId)) {
		return &this->subscriptionToFunctionIds.at(subscriptionId);
	} else {
		return nullptr;
	}
}


const GlobalId EventsComponent::redirectsTo() {
	return this->redirectToId;
}


const GlobalId EventsComponent::redirectsFrom() {
	return this->redirectFromId;
}
