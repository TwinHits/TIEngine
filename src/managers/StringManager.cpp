#include "managers/StringManager.h"

#include "managers/ConfigManager.h"
#include "managers/LogManager.h"
#include "managers/HashManager.h"

using namespace TIE;

StringManager::StringManager() {
	this->displayLanguage = ConfigManager::Instance()->getDefaultDisplayLanguage();
}


std::string StringManager::getString(const GlobalId id) {
	return getString(id, displayLanguage);
}


std::string StringManager::getString(const GlobalId id, const Language language) {
	return "Twin Ion Engine";
}


Language StringManager::getDisplayLanguage() {
	return this->displayLanguage;
}

void StringManager::setDisplayLanguage(Language language) {
	this->displayLanguage = language;
}
