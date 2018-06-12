#ifndef SCENENODE_H
#define SCENENODE_H

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

namespace TIE {

class SceneNode : public sf::Drawable, sf::Transformable, private sf::NonCopyable {
	public:
		SceneNode();
		~SceneNode();

		void setDrawn(bool);
		bool getDrawn();

		void setParent(SceneNode*);
		SceneNode& getParent();

		void draw(sf::RenderWindow&, sf::RenderStates&) const;

		void attachChild(std::unique_ptr<SceneNode>);
		std::unique_ptr<SceneNode> detachChild(const SceneNode&);

		bool operator==(const SceneNode&) const;
		bool operator!=(const SceneNode&) const;

	private:
		virtual void drawSelf(sf::RenderWindow&, sf::RenderStates&) const = 0;

		bool drawn = false;
		SceneNode* parent = nullptr;
		std::vector<std::unique_ptr<SceneNode> > children;
};

}
#endif
