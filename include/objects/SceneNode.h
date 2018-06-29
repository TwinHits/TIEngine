#ifndef SCENENODE_H
#define SCENENODE_H

#include <memory>
#include <set>
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

		virtual sf::FloatRect getBoundingRect() const;

		sf::Transform getWorldTransform() const;
		sf::Vector2f getWorldPosition() const;
		float getWorldRotation() const;
		
		void checkSceneCollisions(SceneNode&, std::set<std::pair<SceneNode*, SceneNode*> >&);
		void checkNodeCollisions(SceneNode&, std::set<std::pair<SceneNode*, SceneNode*> >&);

		void update(const float);
		void draw(sf::RenderTarget&, sf::RenderStates) const;

		SceneNode& attachChild(std::unique_ptr<SceneNode>);
		std::unique_ptr<SceneNode> detachChild(const SceneNode&);

		bool collision(SceneNode&, SceneNode&) const;

		bool operator==(const SceneNode&) const;
		bool operator!=(const SceneNode&) const;

	private:
		virtual void updateSelf(const float) = 0;
		virtual void drawSelf(sf::RenderTarget&, sf::RenderStates) const = 0;

		GlobalId id;
		std::string name = "undefined";
		bool drawn = false;
		SceneNode* parent = nullptr;
		bool collidable = false;
		std::vector<std::unique_ptr<SceneNode> > children;
};

}
#endif

