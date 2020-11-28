#include "interfaces/TIEngineInterface.h"

#include <string>

#include "managers/AssetsManager.h"
#include "managers/WindowManager.h"

using namespace TIE;

bool TIEngineInterface::isValid() {
    return this != nullptr;
}

bool TIEngineInterface::registerTexturesDirectory(const std::string& directory) {
    return AssetsManager::Instance()->loadTexturesFromPath(this->getScriptWorkingDirectory() + directory);
}

bool TIEngineInterface::setWindowSize(const int width, const int height) {
	WindowManager::Instance()->updateWindowSize(width, height);
    return true;
}

bool TIEngineInterface::setWindowTitle(const std::string& title) {
	WindowManager::Instance()->setTitle(title);
    return true;
}

const std::string& TIEngineInterface::getScriptWorkingDirectory() {
    return this->scriptWorkingDirectory;
}

void TIEngineInterface::setScriptWorkingDirectory(const std::string& scriptWorkingDirectory) {
    this->scriptWorkingDirectory = scriptWorkingDirectory;
}