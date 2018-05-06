#ifndef STRINGMANAGER_H
#define STRINGMANAGER_H

#include <string>
#include <map>

#include "templates/Singleton.h"

#include "objects/GlobalId.h"
#include "objects/enumeration/Language.h"

namespace TIE {

class StringManager : public Singleton<StringManager> {
	public:
		std::string getString(const GlobalId id);
		std::string getString(const GlobalId id, const Language language);

		Language getDisplayLanguage();
		void setDisplayLanguage(Language language);
		
		StringManager();
		~StringManager();
	private:
		Language displayLanguage;

		StringManager(const StringManager&);
		void operator=(const StringManager&);
	};

}
#endif
