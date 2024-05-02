#include "objects/components/MessagesComponent.h"

#include "objects/Message.h"
#include "objects/GlobalId.h"

using namespace TIE;

void MessagesComponent::subscribe(GlobalId subscriptionId, std::function<void(std::shared_ptr<Message>)> onMessage) {
    if (!this->subscriptions.count(subscriptionId)) {
        this->subscriptions[subscriptionId];
    }
    this->subscriptions[subscriptionId].push_back(onMessage);
}