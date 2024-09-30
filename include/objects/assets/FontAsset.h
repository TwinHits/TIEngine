#ifndef FONTASSET_H
#define FONTASSET_H

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/GlobalId.h"

namespace TIE {

class FontAsset : public sf::Font {
    public:
        FontAsset(const std::string&, const GlobalId);

        const std::string& getName();
        const std::string& getName() const;
        GlobalId getId();

        ~FontAsset() {};
    private:
        std::string name;
        GlobalId id;
};

}

#endif
