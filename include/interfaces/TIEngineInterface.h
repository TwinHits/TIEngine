#ifndef TIENGINEINTERFACE_H
#define TIENGINEINTERFACE_H

#include <string>

#include <sol/sol.hpp>

namespace TIE {

class TIEngineInterface {
    public:
        TIEngineInterface(sol::state&);
        ~TIEngineInterface() {};

        bool isValid();

        bool registerTexturesDirectory(const std::string&);
        bool registerFontsDirectory(const std::string&);
        bool registerAudioDirectory(const std::string&);

        bool setWindowSize(const int, const int);
        bool setWindowTitle(const std::string&);

        bool registerLevel(const std::string&, const sol::table&);
        bool setLevel(const std::string&);

        bool registerTIEntityDefinition(const std::string&, const sol::table&);
        bool spawnTIEntity(const std::string&);
};

}

#endif