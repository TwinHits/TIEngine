#include "objects/Message.h"
#include "objects/SceneObject.h"
#include "objects/GlobalId.h"

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
