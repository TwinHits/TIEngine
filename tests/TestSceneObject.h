#ifndef TESTSCENEOBJECT_H
#define TESTSCENEOBJECT_H

#include "../src/objects/SceneObject.h"

class TestSceneObject : public SceneObject
{
	public:
		void update();
		void receiveMessage(const Message& msg);
		void testAction(const SceneObject& target);

		TestSceneObject(unsigned long id);
		~TestSceneObject();
	private:

};

#endif
