#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "objects/GlobalId.h"

namespace TIE {

class MessageManager : public Singleton<MessageManager>, public Manager {
	public:
		void subscribe(const std::string&, std::function<void()>);
		void publish(const std::string&);

		const GlobalId getSubscriptionId(const std::string& subscription);
		const std::map<const std::string, GlobalId>& getSubscriptionIds();

		MessageManager() {};
		~MessageManager() {};
	private:
		std::map<const std::string, GlobalId> subscriptionIds;
		// map of subscription id to function pointer with no args that returns void
		std::map<const std::string, std::vector<std::function<void()>>> subscriptions;

		MessageManager(const MessageManager&);
		void operator=(const MessageManager&) {};
};

}
#endif
