#include "componentsystems/EventsComponentSystem.h"

#include "componentsystems/MessagesComponentSystem.h"
#include "managers/EventsManager.h"
#include "managers/MessageManager.h"
#include "managers/ScriptManager.h"
#include "managers/WorldManager.h"
#include "objects/GlobalId.h"
#include "objects/components/EventsComponent.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

EventsComponentSystem::EventsComponentSystem() {
	this->setName(EventsComponentSystem::EVENTS);
}


void EventsComponentSystem::update(const float delta) {

	// Get the next set of messages
	this->currentFrameEvents.clear();
	std::swap(this->currentFrameEvents, this->nextFrameEvents);

	// For each tientity that cares about events
	for (auto& c : this->components) {

		// For each subscription id that has an event
		for (auto& [subscriptionId, messages] : this->currentFrameEvents) {

			// If this tientity cares about this event
			if (c.eventsComponent.hasHandlersFor(subscriptionId) || c.eventsComponent.hasFunctionIdsFor(subscriptionId)) {

				// For each message for this event
                for (auto& message : messages) {

					// If this message is for anyone or for a specific recipient
					if (!message.recipientId || message.recipientId == c.tientity.getId()) {

						// For each handler for this subscriptionId
						for (auto& onMessage : *c.eventsComponent.getHandlersFor(subscriptionId)) {

							// If the message is still valid
							if (message.valid) {
								onMessage(message);
							} else {
								break;
							}
						}

						// For each functionId from this subscriptionId
						for (auto functionId : *c.eventsComponent.getFunctionIdsFor(subscriptionId)) {

							// If the message is still valid
							if (message.valid) {
								ScriptManager::Instance()->runFunction<sol::optional<bool>>(functionId, c.tientity);
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


EventsComponent& EventsComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<EventsComponent>()) {
        EventsComponent& eventsComponent = tientity.addComponent<EventsComponent>();
        this->components.push_back({ eventsComponent, tientity });
        return eventsComponent;
	} else {
		return *tientity.getComponent<EventsComponent>();
	}
}


EventsComponent& EventsComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& entity) {
	EventsComponent& eventsComponent = this->addComponent(entity);
	const ScriptTableReader& reader = factory.getReader().getReader(EventsComponentSystem::EVENTS);

	for (auto& pair : reader.getValues<GlobalId>()) {
		const GlobalId subscriptionId = MessagesComponentSystem::Instance()->registerMessageSubscription(pair.first);
		GlobalId functionId = pair.second;
		eventsComponent.subscribe(subscriptionId, functionId);
	}

	return eventsComponent;
}


bool EventsComponentSystem::removeComponent(TIEntity& tientity) {
	EventsComponent* eventsComponent = tientity.getComponent<EventsComponent>();
	if (eventsComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->eventsComponent == eventsComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<EventsComponent>();
	} else {
		return false;
	}
}


void EventsComponentSystem::subscribe(TIEntity& tientity, const GlobalId subscriptionId, std::function<void(Message&)> handler) {
	EventsComponent& eventsComponent = this->addComponent(tientity);
	eventsComponent.subscribe(subscriptionId, handler);
}


void EventsComponentSystem::publish(Message message) {
	message = this->setSenderId(message);
	message = this->setRecipientId(message);
	if (!this->nextFrameEvents.count(message.subscription)) {
		this->nextFrameEvents[message.subscription];
	}
	this->nextFrameEvents[message.subscription].push_back(message);
}


Message& EventsComponentSystem::setSenderId(Message& message) {
	TIEntity* sender = WorldManager::Instance()->getTIEntityById(message.senderId);
	if (sender) {
		EventsComponent& eventsComponent = this->addComponent(*sender);
		if (eventsComponent.redirectsFrom()) {
			message.senderId = eventsComponent.redirectsFrom();
		}
	}
	return message;
}


Message& EventsComponentSystem::setRecipientId(Message& message) {
	TIEntity* recipient = WorldManager::Instance()->getTIEntityById(message.recipientId);
	if (recipient) {
		EventsComponent& eventsComponent = this->addComponent(*recipient);
		if (eventsComponent.redirectsTo()) {
			message.recipientId = eventsComponent.redirectsTo();
		}
	}
	return message;
}


