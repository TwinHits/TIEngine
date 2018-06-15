#ifndef SCENENODE_H
#define SCENENODE_H

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

namespace TIE {

class SceneNode {
	public:
		SceneNode();
		SceneNode(const SceneNode&);
		virtual ~SceneNode();

		void setDrawn(bool);
		bool getDrawn() const;

		void setParent(SceneNode*);
		SceneNode& getParent();

		void draw(sf::RenderWindow&, sf::RenderStates) const;

		void update(const float);

		SceneNode& attachChild(std::unique_ptr<SceneNode>);
		std::unique_ptr<SceneNode> detachChild(const SceneNode&);

		bool operator==(const SceneNode&) const;
		bool operator!=(const SceneNode&) const;

	private:
		virtual void drawSelf(sf::RenderWindow&, sf::RenderStates) const = 0;
		virtual void updateSelf(const float) = 0;

		bool drawn = false;
		SceneNode* parent = nullptr;
		std::vector<std::unique_ptr<SceneNode> > children;
};

}
#endif
