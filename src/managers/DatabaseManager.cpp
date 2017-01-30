#include "DatabaseManager.h"
#include "LogManager.h" 

using namespace TIE;

DatabaseManager::DatabaseManager()
{
	try 
	{
		db.open(*soci::factory_postgresql(), "dbname=tiengine user=tie_admin password=123456 hostaddr=127.0.0.1 port=5432");
		LogManager::Instance()->logInfo("Successfully opened postgres db connection.");
	}
	catch (const std::exception& e)
	{
		LogManager::Instance()->logError("Postgres db exception: " + std::string(e.what()));
	}
}

DatabaseManager::~DatabaseManager()
{
	db.close();
}

void DatabaseManager::Select(const std::string& q, std::string& s)
{
	try 
	{
		soci::indicator ind;
		db << q, soci::into(s, ind);
	}
	catch (const std::exception& e)
	{
		LogManager::Instance()->logError("Postgres db exception: " + std::string(e.what()));
	}
}
