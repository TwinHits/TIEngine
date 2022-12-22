#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include <SFML/Graphics.hpp>

#include "objects/assets/FontAsset.h"
#include "objects/components/Component.h"
#include "objects/enumeration/TextAlignment.h"

namespace TIE {

class TextComponent : public Component, public sf::Text {
	public:
		TextComponent();
		virtual ~TextComponent() {};

		void setString(const std::string&);

		void setDrawn(bool drawn);
		bool isDrawn() const;

		void setTextAlignment(TextAlignment alignment);
		TextAlignment getTextAlignment() const;

		void setFont(const FontAsset&);
		const FontAsset& getFont();
		const FontAsset& getFont() const;

		const sf::Text& getText();
	private:
		bool drawn = false;
		TextAlignment textAlignment = TextAlignment::TOP_LEFT;
		const FontAsset* fontAsset = nullptr;
};

}
#endif
