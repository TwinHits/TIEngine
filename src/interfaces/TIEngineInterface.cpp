#include "interfaces/TIEngineInterface.h"

#include <string>

#include "managers/AssetsManager.h"

using namespace TIE;

bool TIEngineInterface::isValid() {
    return this != nullptr;
}

bool TIEngineInterface::registerTexturesDirectory(const std::string& directory) {
    return AssetsManager::Instance()->loadTexturesFromPath(this->getScriptWorkingDirectory() + directory);
}

const std::string& TIEngineInterface::getScriptWorkingDirectory() {
    return this->scriptWorkingDirectory;
}

void TIEngineInterface::setScriptWorkingDirectory(const std::string& scriptWorkingDirectory) {
    this->scriptWorkingDirectory = scriptWorkingDirectory;
}