#include "pch.h"

#include "Constants.h"

//Test that a connection to the database is made successfully in the constructor
TEST(DatabaseManager, ConnectToDatabase) {
	//In case a test config is loaded from other tests, load the engine default file
	TIE::ConfigManager::Instance()->loadConfigFile("../../config.ini");
	//This will except if there is a problem.
	TIE::DatabaseManager::Instance();
}

//Test that a select statement runs correctly
TEST(DatabaseManager, RunSelect) {
	std::string expected = TWIN_ION_ENGINE_EN;
	std::string query = "SELECT defaultcontent FROM tie_languagestrings WHERE stringid = 1";
	std::string actual;
	TIE::DatabaseManager::Instance()->Select(query, actual);
	ASSERT_EQ(expected, actual);
}


//It'd be nice if there was a way to test if a connection was closed correctly