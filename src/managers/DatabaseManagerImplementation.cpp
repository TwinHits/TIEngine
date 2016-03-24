#include "DatabaseManager.h"
#include "LogManager.h"

using namespace TIE;

DatabaseManager::DatabaseManager()
{
	try 
	{
		connection = new pqxx::connection("dbname=tiengine user=tie_admin password=123456 hostaddr=127.0.0.1 port=5432");
		if (connection->is_open())
		{
			LogManager::Instance()->logInfo("Successfully opened postgres db connectionn.")
		}
	}
	catch (const std::exception& e)
	{
		LogManager::Instance()->logError("Postgres db connection threw exception.")
	}
}

DatabaseManager::~DatabaseManager()
{
	connection->disconnect();
}
