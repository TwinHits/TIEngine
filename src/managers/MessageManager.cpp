#include "managers/MessageManager.h"
#include "managers/TIEntityManager.h"

using namespace TIE;

MessageManager::MessageManager() {

}


MessageManager::~MessageManager() {

}


void MessageManager::sendMessage(Message msg)  {
	if (msg.getReceiverId() != 0) {
		TIEntityManager::Instance()->getTIEntity(msg.getReceiverId()).receiveMessage(msg);
	} else if (msg.getReceiverId() == 0) {
		auto& entities = TIEntityManager::Instance()->getAllTIEntitys();
		for (auto& e : entities) {
			e.second->receiveMessage(msg);
		}
	}
}
