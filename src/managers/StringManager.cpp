#include "managers/StringManager.h"
#include "managers/LogManager.h"
#include "managers/HashManager.h"
#include "managers/ConfigManager.h"
#include "managers/DatabaseManager.h"

using namespace TIE;

StringManager::StringManager() {
	this->displayLanguage = ConfigManager::Instance()->getDefaultDisplayLanguage();
}


StringManager::~StringManager() {
}


std::string StringManager::getString(const GlobalId id) {
	return getString(id, displayLanguage);
}


std::string StringManager::getString(const GlobalId id, const Language language) {
	std::string result = "";
	std::string query = "SELECT COALESCE((SELECT localizedContent FROM TIE_StringLocalizations WHERE _languageId=" + std::to_string(language) + "), defaultContent) FROM TIE_LanguageStrings LEFT JOIN TIE_StringLocalizations ON stringId=_stringId WHERE stringId =" + std::to_string(id) + " LIMIT 2;";
	DatabaseManager::Instance()->Select(query, result);
	return result;
}


Language StringManager::getDisplayLanguage() {
	return this->displayLanguage;
}

void StringManager::setDisplayLanguage(Language language) {
	this->displayLanguage = language;
}