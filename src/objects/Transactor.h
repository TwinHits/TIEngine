#ifndef TRANSACTOR_H
#define TRANSACTOR_H

#include <pqxx/pqxx>
#include <string>

#include "../managers/LogManager.h"

namespace TIE
{
	class Transactor : public pqxx::transactor<>
	{
		public:
			Transactor(const std::string q, pqxx::result& r) :query(q), output(r)
			{
			}
			void operator()(argument_type& trans)
			{
				result = trans.exec(query);
			}
			void on_commit()
			{
				output = result;
			}
		private:
			const std::string& query;
			pqxx::result& output;
			pqxx::result result;

	};
}
#endif
