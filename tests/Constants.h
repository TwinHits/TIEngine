#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "pch.h"

//General
static std::string TEST_NONSENSE_1 = "memes";
static std::string TEST_NONSENSE_2 = "My fair lady reinforces gender sterotypes";
static std::string TEST_NONSENSE_3 = "memes are the DNA of the soul";
static std::string TEST_NONSENSE_4 = "the non gender specific pronoun's revenge";

//ConfigManager
static std::string TEST_CONFIG_FILE = "../../tests/testconfig.ini";

//AssetsManager
static std::string TEST_TEXTURE = "test_texture.png";
static int TEST_TEXTURE_SIZE_X = 256;
static int DEFAULT_TEXTURE_SIZE_X = 512;
static std::string TEST_FONT = "test_font.ttf";
static std::string TEST_FONT_FAMILY = "Oswald Regular";
static std::string DEFAULT_FONT_FAMILY = "";
static std::string TEST_AUDIO = "test_audio";

//LogLevels
static int COMMAND_INT_VALUE = 0;
static int ERROR_INT_VALUE = 1;
static int WARN_INT_VALUE = 2;
static int INFO_INT_VALUE = 3;

static std::string COMMAND_STRING_VALUE_LC = "command";
static std::string ERROR_STRING_VALUE_LC = "error";
static std::string WARN_STRING_VALUE_LC = "warn";
static std::string INFO_STRING_VALUE_LC = "info";

static std::string COMMAND_STRING_VALUE_UC = "COMMAND";
static std::string ERROR_STRING_VALUE_UC = "ERROR";
static std::string WARN_STRING_VALUE_UC = "WARN";
static std::string INFO_STRING_VALUE_UC = "INFO";

//LogManager
static std::string INFO_LEVEL_PREFIX = "INFO: ";
static std::string WARN_LEVEL_PREFIX = "WARN: ";
static std::string ERROR_LEVEL_PREFIX = "ERROR: ";
static std::string COMMAND_LEVEL_PREFIX = "COMMAND: ";

//StringManager
static std::string TWIN_ION_ENGINE_EN = "Twin Ion Engine";
static std::string TWIN_ION_ENGINE_JP = "Tsuinionenjin";
static TIE::GlobalId TWIN_ION_ENGINE_ID = 1;

//StringToInt 
static std::string ONE = "1";
static std::string TWO = "2";
static std::string THREE = "3";

#endif
