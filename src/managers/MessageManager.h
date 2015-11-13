#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include "../templates/Singleton.h"
#include "../objects/Message.h"

class MessageManager : public Singleton<MessageManager>
{
	public:
		void sendMessage(Message msg);

		MessageManager();
		~MessageManager();
	private:
		MessageManager(const MessageManager&);
		void operator=(const MessageManager&);
};

#endif
