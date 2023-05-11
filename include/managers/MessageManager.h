#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <functional>
#include <map>
#include <vector>

#include "objects/GlobalId.h"

namespace TIE {

	class MessageManager : public Singleton<MessageManager>, Manager {
	public:
		bool initialize();

		void subscribe(const std::string&, std::function<void()>);
		void publish(const std::string&);

		MessageManager() {};
		~MessageManager() {};
	private:
		// map of id to function pointer with no args that returns void
		std::map<const std::string, std::vector<std::function<void()>>> subscriptions;

		MessageManager(const MessageManager&);
		void operator=(const MessageManager&) {};
};

}
#endif
