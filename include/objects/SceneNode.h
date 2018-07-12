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

		const std::vector<std::unique_ptr<SceneNode> >& getChildren() const;

		void setDrawn(bool);
		bool getDrawn() const;

		void setCollidable(bool);
		bool getCollidable() const;

		void setRemove(bool);
		bool getRemove() const;

		virtual sf::FloatRect getHitBox() const;

		sf::Transform getWorldTransform() const;
		sf::Vector2f getWorldPosition() const;
		float getWorldRotation() const;
		
		SceneNode& attachChild(std::unique_ptr<SceneNode>);

		void checkSceneCollisions(SceneNode&, std::set<std::pair<SceneNode*, SceneNode*> >&);
		void checkNodeCollisions(SceneNode&, std::set<std::pair<SceneNode*, SceneNode*> >&);
		virtual void collide(SceneNode*);
		bool collision(SceneNode&, SceneNode&) const;

		void removeNodes();

		void update(const float);
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

		SceneNode* findNode(sf::Vector2f);

		bool operator==(const SceneNode&) const;
		bool operator!=(const SceneNode&) const;

	private:
		virtual void updateSelf(const float) = 0;
		virtual void drawSelf(sf::RenderTarget&, sf::RenderStates) const = 0;

		std::unique_ptr<SceneNode> detachChild(const SceneNode&);

		SceneNode* parent = nullptr;

		GlobalId id;
		std::string type = "Undefined";
		bool drawn = false;
		bool collidable = false;
		bool remove = false;

		std::vector<std::unique_ptr<SceneNode> > children;
};

}
#endif

