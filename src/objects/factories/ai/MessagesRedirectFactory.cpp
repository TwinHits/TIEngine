#include "objects/factories/ai/MessagesRedirectFactory.h"

#include <sol/sol.hpp>

#include "managers/HashManager.h"
#include "objects/ai/MessagesRedirect.h"
#include "templates/MakeUnique.h"

using namespace TIE;

MessagesRedirectFactory::MessagesRedirectFactory() {
    this->id = HashManager::Instance()->getNewGlobalId();
}


std::unique_ptr<MessagesRedirect> MessagesRedirectFactory::build(TIEntity& tientity, TIEntity& redirect) {
    return TIE::make_unique<MessagesRedirect>(tientity, redirect, this->id);
}


GlobalId MessagesRedirectFactory::getId() {
    return this->id;
}
