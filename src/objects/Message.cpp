#include "objects/GlobalId.h"
#include "objects/Message.h"

#include "objects/drawables/TIEntity.h"

using namespace TIE;

Message::Message(GlobalId s, GlobalId r) {
	this->senderId = s;
	this->receiverId = r;
}


Message::Message(GlobalId s) {
	this->senderId = s;
	this->receiverId = 0;
}


TIE::Message::MessageType Message::getMessageType() {
	return type;
}


void Message::setMessageType(MessageType type) {
	this->type = type;
}


void Message::setSenderId(GlobalId id) {
	this->senderId = id;
}


GlobalId Message::getSenderId() { 
	return senderId;
}


void Message::setReceiverId(GlobalId id) { 
	this->receiverId = id;
}


GlobalId Message::getReceiverId() { 
	return receiverId;
}
