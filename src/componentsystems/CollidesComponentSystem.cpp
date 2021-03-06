#include "componentsystems/CollidesComponentSystem.h" 

#include <SFML/Graphics.hpp>

#include "objects/components/CollidesComponent.h"
#include "objects/entities/TIEntity.h"

using namespace TIE;

void CollidesComponentSystem::update(const float delta) {

}

void CollidesComponentSystem::addComponent(const TIEntityFactory& tientityFactory, TIEntity& tientity) {
	
}

bool CollidesComponentSystem::removeComponent(TIEntity& tientity) {
	CollidesComponent* collidesComponent = tientity.getComponent<CollidesComponent>();
	if (collidesComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->collidesComponent == collidesComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<CollidesComponent>();
	} else {
		return false;
	}
}



const std::string& CollidesComponentSystem::getName() {
	return CollidesComponentSystem::COLLIDES;
}

	/*
void CollidesComponentSystem::checkForCollisions() {
	this->collisions.clear();

	SceneLayer& sceneGraphRoot = this->getSceneGraphRoot();
	sceneGraphRoot.checkSceneCollisions(sceneGraphRoot, this->collisions);

	if (!collisions.empty()) {
		for (auto& pair : collisions) {
			pair.first->collide(pair.second);
			pair.second->collide(pair.first);
		}
	}
}

	*/


	/*
sf::FloatRect CollidesComponentSystem::getHitBox() const {
	GraphicsComponent& sprite = this->getComponent<SpriteComponent>();
	return this->getWorldTransform().transformRect(this->sprite.getGlobalBounds());
}

	*/

	/*
bool CollidesComponentSystem::collision(TIEntity& lhs, TIEntity& rhs) const {
	if (!lhs.getCollidable() || !rhs.getCollidable()) {
		return false;
	}
	return lhs.getHitBox().intersects(rhs.getHitBox());
}

	*/
/*
void CollidesComponentSystem::checkForCollisions() {
	this->collisions.clear();
	
	SceneLayer& sceneGraphRoot = this->getSceneGraphRoot();
	sceneGraphRoot.checkSceneCollisions(sceneGraphRoot, this->collisions);

	if (!collisions.empty()) {
		for (auto& pair : collisions) {
			pair.first->collide(pair.second);
			pair.second->collide(pair.first);
		}
	}
}


void CollidesComponentSystem::checkSceneCollisions(TIEntity& sceneGraphRoot, std::set<std::pair<TIEntity*, TIEntity*> >& collisions) {
	this->checkNodeCollisions(sceneGraphRoot, collisions);
	for (auto& child : sceneGraphRoot.children) {
		this->checkSceneCollisions(*child, collisions);
	}	
}


void CollidesComponentSystem::checkNodeCollisions(TIEntity& sceneNode, std::set<std::pair<TIEntity*, TIEntity*> >& collisions) {
	if (*this != sceneNode && collision(*this, sceneNode)) {
		collisions.insert(std::minmax(this, &sceneNode));
	}
	for (auto& child : this->children) {
		child->checkNodeCollisions(sceneNode, collisions);
	}	
}
*/
