#include "componentsystems/CollidesComponentSystem.h" 

#include "componentsystems/MessagesComponentSystem.h" 
#include "managers/ScriptManager.h"
#include "objects/components/CollidesComponent.h"
#include "objects/tientities/TIEntity.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

CollidesComponentSystem::CollidesComponentSystem() {
	this->setName(CollidesComponentSystem::COLLIDES);
	this->collidedMessageSubscription = MessagesComponentSystem::Instance()->registerMessageSubscription("Collided");
}


void CollidesComponentSystem::update(const float delta) {
	for (auto c = components.begin(); c != components.end(); ++c) {
		auto c2 = c;
		++c2;
		if (c2 == components.end()) {
			break;
		}
		if (c->collidesComponent.isCollidable()) {
			sf::FloatRect hitbox = ComponentSystems::getGlobalBounds(c->tientity);
			for (c2; c2 != components.end(); c2++) {
				if (c2->collidesComponent.isCollidable()) {
					sf::FloatRect hitbox2 = ComponentSystems::getGlobalBounds(c2->tientity);
					if (hitbox.intersects(hitbox2)) {
						MessagesComponentSystem::Instance()->sendMessage(
							this->collidedMessageSubscription,
							c->tientity.getId(),
							c2->tientity.getId(),
							ScriptManager::Instance()->getObjectFromValue(c->tientity.getId()));
						MessagesComponentSystem::Instance()->sendMessage(
							this->collidedMessageSubscription,
							c2->tientity.getId(),
							c->tientity.getId(),
							ScriptManager::Instance()->getObjectFromValue(c2->tientity.getId()));
					}
				}
			}
		}
	}
}


CollidesComponent& CollidesComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<CollidesComponent>()) {
        CollidesComponent& collidesComponent = tientity.addComponent<CollidesComponent>();
        this->components.push_back({ collidesComponent, tientity });
        return collidesComponent;
	} else {
		return *tientity.getComponent<CollidesComponent>();
	}
}


CollidesComponent& CollidesComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
	CollidesComponent& collidesComponent = this->addComponent(tientity);
	bool collides  = ComponentSystems::getFactoryValue<bool>(factory, CollidesComponentSystem::IS_COLLIDABLE, collidesComponent.isCollidable(), tientity);
	collidesComponent.setCollidable(collides);
	/**
	collides could be a setting on the shape or the sprite whcih creates a collidescomponent
	or collides could be its own block like normal that references the shape or sprite
	what would that look like?
	Sprite and Shape could add the component if they ahve a collides setting as a reqquired component. That makes sense. 

	1. Add Collides as required component for Sprite and shape.
	How can collides access sprite vs shape to get the right reference?  I think it's just a a transformable. I think for now we can proritize sprite over shape.
	2. Get the sprite or shape and save the reference in Collides
	3. For each collides component, check if it collides with any other collides component.
	4. Save collides in a map by TIEntity id.
		std::Map<GlobalId, std::Map<GlobalId, TIEntity*> >
	5. If getProperty(collisions) return vector of TIEntityInterfaces that collide.
	7. Or figure out a way to send system messages
		1. Collides Consturctor adds a subscription for colliding
	**/

	return collidesComponent;
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
