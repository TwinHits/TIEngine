#ifndef SCENETEXT_H
#define SCENETEXT_H

#include <SFML/Graphics.hpp>

#include "Message.h"
#include "GlobalId.h"

namespace TIE {

class Message;

class SceneText {
	public:
		SceneText();
		virtual ~SceneText();

		GlobalId getId() const;
		void setText(const sf::Text& text);
		sf::Text& getText();
		const sf::Text& getText() const;
		void setDraw(bool b);
		bool getDraw() const;

		virtual void update();
		virtual void receiveMessage(const Message& msg) const;

		bool operator==(const SceneText& rhs) const;
		bool operator!=(const SceneText& rhs) const;
		void operator=(const SceneText&);
	
	protected:
		sf::Text text;
		sf::Clock& clock;
		GlobalId id;
		bool draw = true;
};

}
#endif
