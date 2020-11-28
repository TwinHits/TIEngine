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

    private:
};

}

#endif