#include "objects/ai/MessagesRedirect.h"

#include "componentsystems/BehavesComponentSystem.h"
#include "objects/Message.h"

using namespace TIE;

MessagesRedirect::MessagesRedirect(TIEntity& tientity, TIEntity& redirect, const GlobalId factoryId): 
    redirect(redirect), 
    FiniteStateMachine(tientity, factoryId) {}


void MessagesRedirect::onMessage(const Message& message) {
    BehavesComponentSystem::Instance()->onMessage(this->redirect, message);
}