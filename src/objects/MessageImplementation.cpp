#include "Message.h"
#include "SceneObject.h"

Message::Message(const SceneObject& s, const SceneObject& r) : sender(s), receiver(r) 
{
}
