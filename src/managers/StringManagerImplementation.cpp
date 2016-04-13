#include "StringManager.h"
#include "LogManager.h"
#include "HashManager.h"
#include "ConfigManager.h"
#include "DatabaseManager.h"

using namespace TIE;

StringManager::StringManager()
{
	this->displayLanguage = ConfigManager::Instance()->getDefaultDisplayLanguage();
}

StringManager::~StringManager() {}

std::string StringManager::getString(const GlobalId id)
{
	return getString(id, displayLanguage);
}

std::string StringManager::getString(const GlobalId id, const Language l)
{

	std::string query = "SELECT COALESCE((SELECT localizedContent FROM TIE_StringLocalizations WHERE _languageId=" + std::to_string(l) + "), defaultContent) FROM TIE_LanguageStrings LEFT JOIN TIE_StringLocalizations ON stringId=_stringId WHERE stringId =" + std::to_string(id) + " LIMIT 1;";
	Result result;
	DatabaseManager::Instance()->Select(query, result);
	
	std::string s;
	for (auto i : result)
	{
		for (auto j : i)
		{
			s = j.c_str();
		}
	}

	return s;
}

void StringManager::setDisplayLanguage(Language l)
{
	this->displayLanguage = l;
}
