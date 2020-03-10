#ifndef TIEXT_H
#define TIEXT_H

#include <SFML/Graphics.hpp>

#include "objects/SceneNode.h"

namespace TIE {

class TIExt : public SceneNode {
	public:
		TIExt();
		virtual ~TIExt();

		void setText(const sf::Text&);
		sf::Text& getText();
		const sf::Text& getText() const;
		void setTextString(const std::string&);

		bool operator==(const TIExt&) const;
		bool operator!=(const TIExt&) const;
		void operator=(const TIExt&);
	
	protected:
		virtual void drawSelf(sf::RenderTarget&, sf::RenderStates) const;
		virtual void updateSelf(const float);

		sf::Text text;
};

}
#endif
