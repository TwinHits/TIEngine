#ifndef MESSAGE_H
#define MESSAGE_H


#include "TIEntity.h"
#include "GlobalId.h"

namespace TIE {

class TIEntity;

class Message {
	public:

		struct MoveMsg {
			//msg.move.dest
			//Move specific data
			int dest;
		};
		
		enum MessageType {
			//Possible messages to send;
			Move
		};
	
		Message(GlobalId s, GlobalId r);
		Message(GlobalId s);

		void setMessageType(MessageType type);
		MessageType getMessageType();

		void setSenderId(GlobalId id);
		GlobalId getSenderId();

		void setReceiverId(GlobalId id);
		GlobalId getReceiverId();

		union {
			//Registry of the possible messages?
			MoveMsg move;
		};

	private:
		MessageType type;
		GlobalId senderId;
		GlobalId receiverId;	

};

}
#endif
