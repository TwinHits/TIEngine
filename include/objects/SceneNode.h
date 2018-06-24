#ifndef SCENENODE_H
#define SCENENODE_H

#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "objects/GlobalId.h"

namespace TIE {

class SceneNode : public sf::Transformable, sf::Drawable {
	public:
		SceneNode();
		SceneNode(const SceneNode&);
		virtual ~SceneNode();

		GlobalId getId() const;

		void setName(const std::string&);
		std::string getName() const;

		void setDrawn(bool);
		bool getDrawn() const;

		void setParent(SceneNode*);
		SceneNode& getParent();

		void setCollidable(bool);
		bool getCollidable() const;

		void draw(sf::RenderTarget&, sf::RenderStates) const;

		void update(const float);

		SceneNode& attachChild(std::unique_ptr<SceneNode>);
		std::unique_ptr<SceneNode> detachChild(const SceneNode&);

		bool operator==(const SceneNode&) const;
		bool operator!=(const SceneNode&) const;

	private:
		virtual void drawSelf(sf::RenderTarget&, sf::RenderStates) const = 0;
		virtual void updateSelf(const float) = 0;

		GlobalId id;
		std::string name = "undefined";
		bool drawn = false;
		SceneNode* parent = nullptr;
		bool collidable = false;
		std::vector<std::unique_ptr<SceneNode> > children;

};

}
#endif

