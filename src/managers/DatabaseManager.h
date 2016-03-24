#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <pqxx/pqxx>

#include "../templates/Singleton.h"

namespace TIE
{
	class DatabaseManager : public Singleton<DatabaseManager>
	{
		public:
			pqxx::connection* connection;

			~DatabaseManager();
			DatabaseManager();
		private:

			DatabaseManager(const DatabaseManager&);
			void operator=(const DatabaseManager&);
	};
}

#endif
