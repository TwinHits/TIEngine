#include "managers/ConfigManager.h"
#include "managers/DatabaseManager.h"
#include "managers/LogManager.h" 

using namespace TIE;

DatabaseManager::DatabaseManager() {
	try {
		db.open(*soci::factory_postgresql(), TIE::ConfigManager::Instance()->getDatabaseConnectionString());
		LogManager::Instance()->logInfo("Successfully opened postgres db connection.");
	}
	catch (const std::exception& e) {
		LogManager::Instance()->logError("Postgres db exception: " + std::string(e.what()));
		throw e;
	}
}

DatabaseManager::~DatabaseManager() {
	db.close();
}

void DatabaseManager::Select(const std::string& q, std::string& s) {
	try {
		soci::indicator ind;
		db << q, soci::into(s, ind);
	}
	catch (const std::exception& e) {
		LogManager::Instance()->logError("Postgres db exception: " + std::string(e.what()));
	}
}