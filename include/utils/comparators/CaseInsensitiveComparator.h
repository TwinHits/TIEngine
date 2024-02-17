#include "utils/StringHelpers.h"

namespace TIE {
    struct CaseInsensitiveCompare {
        bool operator()(const std::string& str1, const std::string& str2) const {
            std::string str1Upper = str1;
            std::string str2Upper = str2;
            return TIE::String::toUpper(str1Upper) < TIE::String::toUpper(str2Upper);;
        }
    };
}