#include "managers/ConfigManager.h"
#include "managers/DatabaseManager.h"
#include "managers/LogManager.h" 

using namespace TIE;

DatabaseManager::DatabaseManager() {
	try {
		this->connectionString = TIE::ConfigManager::Instance()->getDatabaseConnectionString();

		for (std::size_t i = 0; i < this->CONNECTION_POOL_SIZE; ++i) {
			soci::session& s = this->connectionPool.at(i);
			s.open(*soci::factory_postgresql(), this->connectionString);
		}

		LogManager::Instance()->logInfo("Successfully opened postgres db connection.");
	} catch (const std::exception& e) {
		LogManager::Instance()->logError("Postgres db exception: " + std::string(e.what()));
		throw e;
	}
}

DatabaseManager::~DatabaseManager() {
	for (std::size_t i = 0; i < CONNECTION_POOL_SIZE; ++i) {
		connectionPool.at(i).close();
	}
}

void DatabaseManager::Select(const std::string& q, std::string& s) {
	try {
		soci::session& engineConnection(this->getConnection());
		soci::indicator ind;
		engineConnection << q, soci::into(s, ind);
	} catch (const std::exception& e) {
		LogManager::Instance()->logError("Postgres db exception: " + std::string(e.what()));
	}
}

soci::session& DatabaseManager::getConnection() {
	std::size_t i = connectionPool.lease();
	return connectionPool.at(i);
}
