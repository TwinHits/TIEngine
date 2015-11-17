#ifndef MESSAGE_H
#define MESSAGE_H

class SceneObject;

#include "SceneObject.h"

class Message 
{
	public:
		Message(unsigned long s, unsigned long r);
		Message(unsigned long s);

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
		unsigned long senderId;
		unsigned long receiverId;	

		union 
		{
			//Registry of the possible messages?
			MoveMsg move;
		};

};

#endif
