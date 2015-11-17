#include "TestSceneObject.h"

#include "../src/managers/MessageManager.h"
#include "../src/managers/LogManager.h"

TestSceneObject::TestSceneObject() : SceneObject()
{
}

TestSceneObject::~TestSceneObject()
{
}

void TestSceneObject::testAction(unsigned long target)
{
	Message msg(this->getId(), target);
	msg.type = Message::Move;
	MessageManager::Instance()->sendMessage(msg);
}

void TestSceneObject::update()
{
}

void TestSceneObject::receiveMessage(const Message& msg)
{
	if (msg.receiverId == this->getId())
	{
		switch (msg.type)
		{
			case Message::Move:
					LogManager::Instance()->logInfo("Sucessful 'Move' message receieved");
				break;
			default:
				break;
		}
	}
}
