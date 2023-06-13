#ifndef MESSAGESREDIRECT_H
#define MESSAGESREDIRECT_H

#include "objects/GlobalId.h"
#include "objects/Message.h"
#include "objects/ai/FiniteStateMachine.h"

namespace TIE {

class MessagesRedirect : public FiniteStateMachine {
    public:
        MessagesRedirect(TIEntity&, TIEntity&, const GlobalId);

        void onMessage(const Message&);

    private:
        TIEntity& redirect;
    };

}

#endif
