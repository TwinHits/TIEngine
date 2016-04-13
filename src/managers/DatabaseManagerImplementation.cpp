#include "DatabaseManager.h"
#include "LogManager.h" 
#include "../objects/Transactor.h"

using namespace TIE;

DatabaseManager::DatabaseManager()
{
	try 
	{
		connection = std::unique_ptr<pqxx::connection>(new pqxx::connection("dbname=tiengine user=tie_admin password=123456 hostaddr=127.0.0.1 port=5432"));
		if (connection->is_open())
		{
			LogManager::Instance()->logInfo("Successfully opened postgres db connectionn.");
		}
	}
	catch (pqxx::pqxx_exception& e)
	{
		LogManager::Instance()->logError("Postgres db connection threw exception.");
	}
}

DatabaseManager::~DatabaseManager()
{
	connection->disconnect();
}

void DatabaseManager::Select(const std::string& q, Result& r)
{
	Transactor t(q, r);

	try
	{
		connection->perform(t);
	}
	catch (std::exception& err)
	{
		std::string what = err.what();
		LogManager::Instance()->logError("Database transaction failed: " + what);
	}
}
