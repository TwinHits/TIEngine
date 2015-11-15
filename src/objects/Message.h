#ifndef MESSAGE_H
#define MESSAGE_H

class SceneObject;

#include "SceneObject.h"

class Message 
{
	public:
		Message(const SceneObject& s, const SceneObject& r);

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
		const SceneObject& sender;
		const SceneObject& receiver;

		union 
		{
	//Registry of the possible messages?
			MoveMsg move;
		};

};

#endif
