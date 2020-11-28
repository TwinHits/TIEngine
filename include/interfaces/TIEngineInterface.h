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
        bool registerFontsDirectory(const std::string&);
        bool registerAudioDirectory(const std::string&);

        bool setWindowSize(const int, const int);
        bool setWindowTitle(const std::string&);

        void setScriptWorkingDirectory(const std::string&);
        const std::string& getScriptWorkingDirectory();

    private:
        std::string scriptWorkingDirectory = "";
};

}

#endif