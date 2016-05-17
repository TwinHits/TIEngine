#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <soci.h>
#include <soci-postgresql.h>

#include <memory>
#include <string>

#include "../templates/Singleton.h"

namespace TIE
{
	class DatabaseManager : public Singleton<DatabaseManager>
	{
		public:
			void Select(const std::string& query, std::string& s);

			DatabaseManager();
			~DatabaseManager();
		private:
			soci::session db;

			DatabaseManager(const DatabaseManager&);
			void operator=(const DatabaseManager&);
	};
}

#endif
