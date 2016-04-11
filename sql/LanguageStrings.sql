CREATE TABLE TIE_LanguageStrings (
	stringId         serial     PRIMARY KEY                                NOT NULL,
	defaultContent   text                                                  NOT NULL);

CREATE TABLE TIE_Languages (
	languageId       serial     PRIMARY KEY                                NOT NULL,
	languageName     char(5)                                               NOT NULL);

CREATE TABLE TIE_StringLocalizations (
	_stringId        serial     REFERENCES TIE_LanguageStrings(stringId)   NOT NULL,
	_languageId 	 serial     REFERENCES TIE_Languages(languageId)     NOT NULL,
	localizedContent text);


INSERT INTO TIE_Languages (languageId, languageName) VALUES (0, 'en_US');
INSERT INTO TIE_Languages (languageId, languageName) VALUES (1, 'fe_FR');
INSERT INTO TIE_Languages (languageId, languageName) VALUES (2, 'es_ES');
INSERT INTO TIE_Languages (languageId, languageName) VALUES (3, 'de_DE');
INSERT INTO TIE_Languages (languageId, languageName) VALUES (4, 'ja_JP');


INSERT INTO TIE_LanguageStrings (stringId, defaultContent) VALUES (default, 'Twin Ion Engine');

INSERT INTO TIE_StringLocalizations (_stringId, _languageId, localizedContent)
VALUES ((SELECT stringId FROM TIE_LanguageStrings
WHERE defaultContent='Twin Ion Engine'), 0, 'Twin Ion Engine');

INSERT INTO TIE_StringLocalizations (_stringId, _languageId, localizedContent)
VALUES ((SELECT stringId FROM TIE_LanguageStrings
WHERE defaultContent='Twin Ion Engine'), 1, 'Lits Ion Engine');

INSERT INTO TIE_StringLocalizations (_stringId, _languageId, localizedContent)
VALUES ((SELECT stringId FROM TIE_LanguageStrings
WHERE defaultContent='Twin Ion Engine'), 3, 'Twin Ion Motor');

INSERT INTO TIE_StringLocalizations (_stringId, _languageId, localizedContent)
VALUES ((SELECT stringId FROM TIE_LanguageStrings
WHERE defaultContent='Twin Ion Engine'), 2, 'Doble Ion Engine');

INSERT INTO TIE_StringLocalizations (_stringId, _languageId, localizedContent)
VALUES ((SELECT stringId FROM TIE_LanguageStrings
WHERE defaultContent='Twin Ion Engine'), 4, 'Tsuinionenjin');
