#include "MessageManager.h"
#include "SceneObjectManager.h"

MessageManager::MessageManager() {}
MessageManager::~MessageManager() {}

void MessageManager::sendMessage(Message msg) 
{
	auto objs = SceneObjectManager::Instance()->getAllSceneObjects();
	for (auto so = objs.begin(); so != objs.end(); ++so)
	{
		so->second->receiveMessage(msg);
	}
}
