#ifndef PARSELANGUAGESTRING_H 
#define PARSELANGUAGESTRING_H

#include <string>

#include "../objects/enumeration/Language.h"

namespace TIE { 

Language parseLanguageString(const std::string& string);

}
#endif 
