#ifndef COMPONENTSYSTEMSTYPES_H
#define COMPONENTSYSTEMSTYPES_H

#include <map>
#include <string>

namespace TIE {
    namespace ComponentSystems {
        typedef std::map<std::string, std::map<std::string, std::string> > ComponentSystemPropertiesMap;
    }
}

#endif
