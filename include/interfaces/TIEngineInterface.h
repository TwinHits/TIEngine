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
        const sf::Vector2i& getWindowSize();

        bool setWindowTitle(const std::string&);
        void setWindowFullScreen(const bool);

        bool setLevel(const sol::table&);

        bool setZoomSettings(const float, const float, const float);

        sol::object spawn(const sol::table&);

        bool hasEvent(std::string& event);
        const sf::Vector2i getMouseClickPosition();

        sol::object getTIEntityById(GlobalId);

        sol::object registerSceneLayer(const std::string&, bool);
        GlobalId registerFiniteStateMachine(const sol::table&);
        GlobalId registerBehaviorTreeNode(const sol::table&);

        const std::map<std::string, std::string>& getBehaviorTreeNodeTypes();
        const std::map<std::string, int>& getBehaviorTreeNodeStatuses();

        GlobalId registerMessageSubscription(const std::string&);
        const std::map<std::string, GlobalId>& getMessageSubscriptions();

        const ComponentSystems::ComponentSystemPropertiesMap& getProperties();
};

}

#endif