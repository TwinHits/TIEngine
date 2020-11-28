#ifndef TIENGINEINTERFACE_H
#define TIENGINEINTERFACE_H

#include <string>

namespace TIE {

class TIEngineInterface {
    public:
        TIEngineInterface() {};
        ~TIEngineInterface() {};

        bool isValid();
        bool registerTexturesDirectory(const std::string&);

        void setScriptWorkingDirectory(const std::string&);
        const std::string& getScriptWorkingDirectory();

    private:
        std::string scriptWorkingDirectory = "";
};

}

#endif