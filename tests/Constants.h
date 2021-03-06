#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "pch.h"

namespace TIE {

//General
static std::string TEST_NONSENSE_1 = "memes";
static std::string TEST_NONSENSE_2 = "My fair lady reinforces gender sterotypes";
static std::string TEST_NONSENSE_3 = "memes are the DNA of the soul";
static std::string TEST_NONSENSE_4 = "the non gender specific pronoun's revenge";

//ConfigManager
static std::string TEST_CONFIG_FILE = "testconfig.ini";
static std::string JUNK_CONFIG_FILE = "junkconfig.ini";

//AssetsManager
static std::string TEST_TEXTURE = "test_texture.png";
static int TEST_TEXTURE_SIZE_X = 256;
static int DEFAULT_TEXTURE_SIZE_X = 512;
static std::string TEST_FONT = "test_font.ttf";
static std::string TEST_FONT_FAMILY = "Oswald Stencil";
static std::string DEFAULT_FONT_FAMILY = "";
static std::string TEST_AUDIO = "test_audio";

//HashManager
static std::string SAME_CONTENT_DIFFERENT_ADDRESS_1 = "memes";

//LogLevels
static int COMMAND_INT_VALUE = 0;
static int ERROR_INT_VALUE = 1;
static int WARN_INT_VALUE = 2;
static int INFO_INT_VALUE = 3;
static int DEBUG_INT_VALUE = 4;

static std::string COMMAND_STRING_VALUE_LC = "command";
static std::string ERROR_STRING_VALUE_LC = "error";
static std::string WARN_STRING_VALUE_LC = "warn";
static std::string INFO_STRING_VALUE_LC = "info";
static std::string DEBUG_STRING_VALUE_LC = "debug";

static std::string COMMAND_STRING_VALUE_UC = "COMMAND";
static std::string ERROR_STRING_VALUE_UC = "ERROR";
static std::string WARN_STRING_VALUE_UC = "WARN";
static std::string INFO_STRING_VALUE_UC = "INFO";
static std::string DEBUG_STRING_VALUE_UC = "DEBUG";

//LogManager
static std::string INFO_LEVEL_PREFIX = " INFO: ";
static std::string WARN_LEVEL_PREFIX = " WARN: ";
static std::string ERROR_LEVEL_PREFIX = " ERROR: ";
static std::string COMMAND_LEVEL_PREFIX = " COMMAND: ";
static std::string DEBUG_LEVEL_PREFIX = " DEBUG: ";

//StringManager
static std::string TWIN_ION_ENGINE_EN = "Twin Ion Engine";
static std::string TWIN_ION_ENGINE_JP = "Tsuinionenjin";
static TIE::GlobalId TWIN_ION_ENGINE_ID = 1;

//StringToInt 
static std::string ONE = "1";
static std::string TWO = "2";
static std::string THREE = "3";

//WindowManager
static std::string SECOND_WINDOW_WARNING = "A window has already been created, resetting and creating a new window.";
static std::string NO_WINDOW_TO_GET_WARNING = "Client attempted to get a window that does not exist. Returning default new window.";

//ViewManager
static sf::Vector2f DEFAULT_VIEW_CENTER = sf::Vector2f(0, 0);
static sf::Vector2f DEFAULT_VIEW_SIZE = sf::Vector2f(800, 600);
static std::string NO_VIEW_TO_REMOVE_WARNING = "No view found by id ";
static std::string NO_VIEW_TO_GET_ERROR = "No view found by id '";
static sf::FloatRect CUSTOM_VIEW_RECT = sf::FloatRect(0, 0, 1000, 1000);
static sf::Vector2f CUSTOM_VIEW_CENTER = sf::Vector2f(0, 0);
static sf::Vector2f CUSTOM_VIEW_SIZE = sf::Vector2f(1000, 1000);
static TIE::GlobalId VIEW_UNUSED_ID = 123151342;
static float SCROLL_SPEED = 5;
static float TEST_SCROLL_SPEED = 50;

//TIEntity
static bool DEFAULT_DRAW_BOOL = false;
static bool CUSTOM_DRAW_BOOL = true;
static int DEFAULT_DRAW_ORDER_INT = 0;
static int CUSTOM_DRAW_ORDER_INT = 12312;
static TIE::GlobalId ENTITY_UNUSED_ID = 99868;
static float DEFAULT_SPEED_FLOAT = 1;
static float CUSTOM_SPEED_FLOAT = 0.5;

//TIExt
static TIE::GlobalId TIEXT_UNUSED_ID = 40003;

//SceneManager
static std::string DELETED_TIENTITY_INFO = "Deleted TIEntity '";
static std::string DELETED_TIEXT_INFO = "Deleted TIExt '";

//MissingSprite
static std::string MISSING_SPRITE_TEXTURE = "missing_texture.png";
static sf::IntRect MISSING_SPRITE_SIZE = sf::IntRect(0, 0, 32, 48);
static sf::Vector2f MISSING_SPRITE_SCALE = sf::Vector2f(2, 2);
static sf::Vector2f MISSING_SPRITE_ORIGIN = sf::Vector2f(16, 48);
static sf::Vector2f MISSING_SPRITE_POSITION = sf::Vector2f(0, 0);

//MissingText
static std::string MISSING_TEXT_FONT = "font.tff";
static std::string MISSING_TEXT_STRING = "NO_TEXT";
static sf::Vector2f MISSING_TEXT_POSITION = sf::Vector2f(0, 0);
static int MISSING_TEXT_CHARACTER_SIZE = 14;

//DevConsole
static std::string TEST_COMMAND = "test";
static std::string TEST_COMMAND_RUN_COMMAND = "Test Command Please Ignore.";
static std::string UNKNOWN_COMMAND_RUN_COMMAND = "Unknown command.";

//ParseLanguageString
static std::string EN_STRING = "en_US";
static std::string ES_STRING = "es_ES";
static std::string FR_STRING = "fe_FR";
static std::string DE_STRING = "de_DE";
static std::string JA_STRING = "ja_JP";

} 
#endif
