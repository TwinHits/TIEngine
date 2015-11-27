#ifndef STRINGMANAGER_H
#define STRINGMANAGER_H

#include <string>
#include <map>

#include "../templates/Singleton.h"

#include "../objects/GlobalId.h"
#include "../objects/Language.h"

namespace TIE
{

	class StringManager : public Singleton<StringManager>
	{
		public:
			const std::string& getString(const std::string& s);
			const std::string& getString(const std::string& s, Language l);
			void addString(const std::string& defaultString, Language l, const std::string& localizedString);
			void addString(const std::string& defaultString);
			void setDisplayLanguage(Language l);
			
			StringManager();
			~StringManager();
		private:
			std::map<unsigned long, std::map<Language, std::string> > locals;

			Language displayLanguage;

			StringManager(const StringManager&);
			void operator=(const StringManager&);
	};

}

#endif
