#include "objects/assets/FontAsset.h"

#include <string>

#include "objects/GlobalId.h"

using namespace TIE;

FontAsset::FontAsset(const std::string& name, const GlobalId id) {
    this->name = name;
    this->id = id;
}


const std::string& FontAsset::getName() {
    return this->name;
}


const std::string& FontAsset::getName() const {
    return this->name;
}


GlobalId FontAsset::getId() {
    return this->id;
}
