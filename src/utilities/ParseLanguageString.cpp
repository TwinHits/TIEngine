#include "utilities/ParseLanguageString.h"

#include <map>
#include <string>

#include "objects/enumeration/Language.h"

TIE::Language TIE::parseLanguageString(const std::string& string) {
	//Take a string and figure out with language it's referring to.

	std::map<std::string, Language> languages;
	languages["en_US"] = en_US;
	languages["es_ES"] = es_ES;
	languages["fe_FR"] = fe_FR;
	languages["de_DE"] = de_DE;
	languages["ja_JP"] = ja_JP;

	TIE::Language l = languages[string];
	if (l == 0) {
		return en_US;
	} else {
		return l;
	}
}
