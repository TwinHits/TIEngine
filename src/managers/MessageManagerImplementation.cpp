#include "MessageManager.h"
#include "SceneObjectManager.h"

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
		for (auto so = sobjs.begin(); so != sobjs.end(); ++so)
		{
			so->second->receiveMessage(msg);
		}
	}
}
