#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <soci.h>
#include <soci-postgresql.h>

#include <string>

#include "templates/Singleton.h"

namespace TIE {

class DatabaseManager : public Singleton<DatabaseManager> {
	public:
		DatabaseManager();
		~DatabaseManager();

		soci::session& getConnection();

		void Select(const std::string& query, std::string& s);

	private:
		std::string connectionString;
		const std::size_t CONNECTION_POOL_SIZE = 10;
		soci::connection_pool connectionPool = soci::connection_pool(CONNECTION_POOL_SIZE);

		DatabaseManager(const DatabaseManager&);
		void operator=(const DatabaseManager&);
};

}
#endif
