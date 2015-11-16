#include "TestSceneObject.h"

#include "../src/managers/MessageManager.h"
#include "../src/managers/LogManager.h"

TestSceneObject::TestSceneObject(unsigned long id) : SceneObject(id)
{
}

TestSceneObject::~TestSceneObject()
{
}

void TestSceneObject::testAction(const SceneObject& target)
{
	Message msg(*this, target);
	msg.type = Message::Move;
	MessageManager::Instance()->sendMessage(msg);
}

void TestSceneObject::update()
{
	
}

void TestSceneObject::receiveMessage(const Message& msg)
{
	if (msg.receiver == *this)
	{
		switch (msg.type)
		{
			case Message::Move:
					LogManager::Instance()->logInfo("Sucessful message receieved");
				break;
			default:
				break;
		}
	}
}
