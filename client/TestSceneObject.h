#ifndef TESTSCENEOBJECT_H
#define TESTSCENEOBJECT_H

#include "../src/TIEngine.h"

class TestSceneObject : public SceneObject
{
	public:
		void update();
		void receiveMessage(const Message& msg);
		void testAction(GlobalId target) const;

		TestSceneObject();
		~TestSceneObject();
	private:

};

#endif
