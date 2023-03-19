#include "interfaces/MessageInterface.h"

#include "objects/Message.h"

using namespace TIE;

MessageInterface::MessageInterface(const Message& message) {
    this->subscription = message.subscription;
    this->senderId = message.senderId;
    this->payload = message.payload;
}


void MessageInterface::registerUserType(sol::state& luaState) {
    sol::usertype<MessageInterface> interfaceUserType = luaState.new_usertype<MessageInterface>("message");

    interfaceUserType["subscription"] = &MessageInterface::subscription;
    interfaceUserType["senderId"] = &MessageInterface::senderId;
    interfaceUserType["payload"] = &MessageInterface::payload;
}

