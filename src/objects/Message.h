#ifndef MESSAGE_H
#define MESSAGE_H

class SceneObject;

#include "SceneObject.h"
#include "GlobalId.h"

class Message 
{
	public:
		Message(GlobalId s, GlobalId r);
		Message(GlobalId s);

		struct MoveMsg 
		{
			//msg.move.dest
			//Move specific data
			int dest;
		};
		
		enum MessageType
	   	{
			//Possible messages to send;
			Move
		};
		
		MessageType type;
		GlobalId senderId;
		GlobalId receiverId;	

		union 
		{
			//Registry of the possible messages?
			MoveMsg move;
		};

};

#endif
