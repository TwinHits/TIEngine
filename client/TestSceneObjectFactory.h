#ifndef TESTOBJECTFACTORY_H
#define TESTOBJECTFACTORY_H

#include "../src/TIEngine.h"

#include "TestSceneObject.h"

class TestSceneObjectFactory : public Factory<TestSceneObject>
{
	public:
		//create(para1, para2, para3);
		TestSceneObjectFactory();
		~TestSceneObjectFactory();
	private:

};

#endif
