#ifndef COMPONENTSYSTEMSTYPES_H
#define COMPONENTSYSTEMSTYPES_H

#include <map>
#include <string>

namespace TIE {
    namespace ComponentSystems {
        typedef std::map<std::string, std::string> ComponentSystemPropertyMap;
        typedef std::map<std::string, ComponentSystemPropertyMap> ComponentSystemPropertiesMap;
    }
}

#endif
