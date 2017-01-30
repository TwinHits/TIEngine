#include "MessageManager.h"
#include "SceneObjectManager.h"

using namespace TIE;

MessageManager::MessageManager() {}
MessageManager::~MessageManager() {}

void MessageManager::sendMessage(Message msg) 
{
	if (msg.receiverId != 0)
	{
		SceneObjectManager::Instance()->getSceneObject(msg.receiverId).receiveMessage(msg);
	}
	else if (msg.receiverId == 0)
	{
		auto sobjs = SceneObjectManager::Instance()->getAllSceneObjects();
		for (auto& so : sobjs)
		{
			so.second->receiveMessage(msg);
		}
	}
}
