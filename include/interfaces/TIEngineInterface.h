#ifndef TIENGINEINTERFACE_H
#define TIENGINEINTERFACE_H

#include <string>

#include <sol/sol.hpp>

#include "interfaces/TIEntityInterface.h"
#include "interfaces/Vector2Interface.h"
#include "objects/GlobalId.h"

namespace TIE {

class TIEngineInterface {
    public:
        TIEngineInterface() {};
        ~TIEngineInterface() {};

        static void registerUserType(sol::state&);

        bool isValid();

        bool registerTexturesDirectory(const std::string&);
        bool registerFontsDirectory(const std::string&);
        bool registerAudioDirectory(const std::string&);

        bool setWindowSize(const int, const int);
        bool setWindowTitle(const std::string&);

        bool setLevel(const sol::table&);

        TIEntityInterface spawn(const sol::table&);

        bool hasEvent(std::string& event);
        Vector2iInterface getMouseClickPosition();

        TIEntityInterface getTIEntityById(GlobalId);

        GlobalId registerBehavior(const std::string&, const sol::function&);

        TIEntityInterface registerSceneLayer(const std::string&);
};

}

#endif