#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <pqxx/pqxx>
#include <string>

#include "../templates/Singleton.h"

namespace TIE
{
	typedef pqxx::result Result;

	class DatabaseManager : public Singleton<DatabaseManager>
	{
		public:
			void Select(const std::string& query, Result& result);

			~DatabaseManager();
			DatabaseManager();
		private:
			pqxx::connection* connection;

			DatabaseManager(const DatabaseManager&);
			void operator=(const DatabaseManager&);
	};
}

#endif