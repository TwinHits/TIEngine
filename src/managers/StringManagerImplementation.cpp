#include <iostream>

#include "StringManager.h"
#include "LogManager.h"
#include "HashManager.h"
#include "ConfigManager.h"

using namespace TIE;

StringManager::StringManager()
{
	this->displayLanguage = ConfigManager::Instance()->getDefaultDisplayLanguage();
}
StringManager::~StringManager() {}

const std::string& StringManager::getString(const std::string& s)
{
	unsigned long hash = HashManager::Instance()->getHash(s);
	if (locals.find(hash) != locals.end())
	{
		if (locals[hash].find(displayLanguage) != locals[hash].end())
			return locals[hash][displayLanguage];
		else
		{
			LogManager::Instance()->logWarn("Cannot find string for language '" + std::to_string(displayLanguage) + "' for string '" + s + "'. Returning passed value.");
			return s;
		}
	}
	else 
	{
		LogManager::Instance()->logError("Cannot find registration for string '" + s + "'. Returning passed value.");
		return s;
	}
}

const std::string& StringManager::getString(const std::string& s, Language l)
{
	unsigned long hash = HashManager::Instance()->getHash(s);
	if (locals.find(hash) != locals.end())
	{
		if (locals[hash].find(l) != locals[hash].end())
			return locals[hash][l];
		else
		{
			LogManager::Instance()->logWarn("Cannot find string for language '" + std::to_string(l) + "' for string '" + s + "'. Returning passed value.");
			return s;
		}
	}
	else
	{
		LogManager::Instance()->logError("Cannot find registration for string '" + s + "'. Returning passed value.");
		return s;
	}
}

void StringManager::addString(const std::string& defaultString)
{
	unsigned long hash = HashManager::Instance()->getHash(defaultString);
	if (locals.find(hash) == locals.end())
	{
		locals[hash][displayLanguage] = defaultString;
	}
	else if (locals.find(hash) != locals.end())
	{
		LogManager::Instance()->logWarn("Overriding localization for '" + std::to_string(displayLanguage) + "' for '" + defaultString + "'.");
		locals[hash][displayLanguage] = defaultString;
	}
}

void StringManager::addString(const std::string& defaultString, Language l, const std::string& localizedString)
{
	unsigned long hash = HashManager::Instance()->getHash(defaultString);
	if (locals.find(hash) == locals.end())
	{
		locals[hash][displayLanguage] = defaultString;
		locals[hash][l] = localizedString;
	}
	else if (locals.find(hash) != locals.end())
	{
		if (locals[hash].find(l) == locals[hash].end())
		{
			locals[hash][l] = localizedString;
		}
		else 
		{
			LogManager::Instance()->logWarn("Overriding localization for '" + std::to_string(l) + "' for '" + defaultString + "'.");
			locals[hash][l] = localizedString;
		}
	}
}

void StringManager::setDisplayLanguage(Language l)
{
	this->displayLanguage = l;
}
