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

		void setType(const std::string&);
		std::string getType() const;

		void setParent(SceneNode*);
		SceneNode& getParent();

		void setDrawn(bool);
		bool getDrawn() const;

		void setCollidable(bool);
		bool getCollidable() const;

		void setRemove(bool);
		bool getRemove() const;

		virtual sf::FloatRect getHitBox() const;

		virtual void collide(SceneNode*);

		sf::Transform getWorldTransform() const;
		sf::Vector2f getWorldPosition() const;
		float getWorldRotation() const;
		
		void checkSceneCollisions(SceneNode&, std::set<std::pair<SceneNode*, SceneNode*> >&);
		void checkNodeCollisions(SceneNode&, std::set<std::pair<SceneNode*, SceneNode*> >&);
		void removeNodes();

		void update(const float);
		void draw(sf::RenderTarget&, sf::RenderStates) const;

		SceneNode& attachChild(std::unique_ptr<SceneNode>);

		bool collision(SceneNode&, SceneNode&) const;

		bool operator==(const SceneNode&) const;
		bool operator!=(const SceneNode&) const;

	private:
		virtual void updateSelf(const float) = 0;
		virtual void drawSelf(sf::RenderTarget&, sf::RenderStates) const = 0;

		std::unique_ptr<SceneNode> detachChild(const SceneNode&);

		GlobalId id;
		std::string type = "Undefined";
		SceneNode* parent = nullptr;
		bool drawn = false;
		bool collidable = false;
		bool remove = false;

		std::vector<std::unique_ptr<SceneNode> > children;
};

}
#endif

