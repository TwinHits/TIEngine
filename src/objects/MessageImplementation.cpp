#include "Message.h"
#include "SceneObject.h"

Message::Message(unsigned long s, unsigned long r)
{
	this->senderId = s;
	this->receiverId = r;
}
Message::Message(unsigned long s)
{
	this->senderId = s;
	this->receiverId = 0;
}
