#include "Message.h"
#include "SceneObject.h"
#include "GlobalId.h"

using namespace TIE;

Message::Message(GlobalId s, GlobalId r)
{
	this->senderId = s;
	this->receiverId = r;
}
Message::Message(GlobalId s)
{
	this->senderId = s;
	this->receiverId = 0;
}
