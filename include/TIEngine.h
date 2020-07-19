/* This is where the lisence agreement would go.
 *
 * This is Twin Ion Engine, a game engine for the SFML graphics library.
 * Include this file, in order to access all the neccessary classes to utilize
 * this libray.
 * * See src/main.cpp for an example of the basic render loop.
 *
 * Glory and gore go hand in hand.
*/

#ifndef TIENGINE_H
#define TIENGINE_H

	#include "managers/AssetsManager.h"
	#include "managers/ConfigManager.h"
	#include "managers/ConsoleManager.h"
	#include "managers/HashManager.h"
	#include "managers/InputManager.h"
	#include "managers/LogManager.h"
	#include "managers/SceneManager.h"
	#include "managers/ScriptManager.h"
	#include "managers/StartUpManager.h"
	#include "managers/StringManager.h"
	#include "managers/TimeManager.h"
	#include "managers/ViewManager.h"
	#include "managers/WindowManager.h"

	#include "templates/Factory.h"
	#include "templates/MakeUnique.h"
	
	#include "utilities/LocalTime.h"
	#include "utilities/ParseLanguageString.h"
	#include "utilities/StringToInt.h"

#endif
