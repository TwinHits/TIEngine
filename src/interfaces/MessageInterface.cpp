#include "interfaces/MessageInterface.h"

#include "objects/Message.h"

using namespace TIE;

MessageInterface::MessageInterface(Message& message) : message(message) {
    this->subscription = message.subscription;
    this->senderId = message.senderId;
    this->payload = message.payload;
}


void MessageInterface::registerUserType(sol::state& luaState) {
    sol::usertype<MessageInterface> interfaceUserType = luaState.new_usertype<MessageInterface>("message");

    interfaceUserType["subscription"] = &MessageInterface::subscription;
    interfaceUserType["senderId"] = &MessageInterface::senderId;
    interfaceUserType["payload"] = &MessageInterface::payload;

    interfaceUserType["isValid"] = &MessageInterface::isValid;
    interfaceUserType["setValid"] = &MessageInterface::setValid;
}

const bool MessageInterface::isValid() {
    return this->message.valid;
}

void MessageInterface::setValid(const bool valid) {
    this->message.valid = valid;
}

