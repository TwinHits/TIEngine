#ifndef MESSAGESREDIRECTFACTORY_H
#define MESSAGESREDIRECTFACTORY_H

#include <memory>

#include "objects/GlobalId.h"
#include "objects/ai/MessagesRedirect.h"

namespace TIE {

class MessagesRedirectFactory {
	public:
		MessagesRedirectFactory();

		std::unique_ptr<MessagesRedirect> build(TIEntity&, TIEntity&);

		GlobalId getId();
	private:
		GlobalId id = 0;
};

}

#endif MESSAGESREDIRECTFACTORY_H
