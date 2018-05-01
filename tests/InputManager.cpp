#include "pch.h"

#include "Constants.h"

TEST(InputManager, SetInputMap) {
	std::unique_ptr<TIE::InputMap> inputMap = TIE::make_unique<TIE::InputMap>();
	TIE::InputManager::Instance()->setInputMap(std::move(inputMap));
	
	TIE::InputManager::Instance()->processInput();
	//No Exception
}


//TEST(InputManager, ProcessInput) {}
