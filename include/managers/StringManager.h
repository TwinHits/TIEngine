#ifndef STRINGMANAGER_H
#define STRINGMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <string>
#include <map>

#include "objects/GlobalId.h"
#include "objects/enumeration/Language.h"

namespace TIE {

class StringManager : public Singleton<StringManager>, Manager {
	public:
		bool initialize();
		
		std::string getString(const GlobalId id);
		std::string getString(const GlobalId id, const Language language);

		Language getDisplayLanguage();
		void setDisplayLanguage(Language language);
		
		StringManager() {};
		~StringManager() {};
	private:
		Language displayLanguage = Language::en_US;

		StringManager(const StringManager&);
		void operator=(const StringManager&) {};
	};

}
#endif
