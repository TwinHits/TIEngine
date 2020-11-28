#include "interfaces/TIEngineInterface.h"

#include <string>

#include "managers/AssetsManager.h"

using namespace TIE;

bool TIEngineInterface::isValid() {
    return this != nullptr;
}

bool TIEngineInterface::registerTexturesDirectory(const std::string& directory) {
    return AssetsManager::Instance()->loadTexturesFromPath(directory);
}