#ifndef TIENGINEINTERFACE_H
#define TIENGINEINTERFACE_H

#include <string>

#include <sol/sol.hpp>

#include "interfaces/TIEntityInterface.h"
#include "objects/GlobalId.h"
#include "utils/types/ComponentSystemsTypes.h"

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
        void setWindowFullScreen(const bool);

        bool setLevel(const sol::table&);

        bool setZoomSettings(const float, const float, const float);

        TIEntityInterface spawn(const sol::table&);

        bool hasEvent(std::string& event);
        const sf::Vector2i getMouseClickPosition();

        TIEntityInterface getTIEntityById(GlobalId);

        TIEntityInterface registerSceneLayer(const std::string&, bool);
        GlobalId registerFiniteStateMachine(const sol::table&);

        GlobalId registerMessageSubscription(const std::string&);
        const std::map<std::string, GlobalId>& getMessageSubscriptions();
        void sendMessage(const GlobalId, sol::object, sol::object);

        const ComponentSystems::ComponentSystemPropertiesMap& getProperties();
};

}

#endif