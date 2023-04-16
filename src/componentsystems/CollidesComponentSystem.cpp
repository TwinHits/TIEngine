#include "componentsystems/CollidesComponentSystem.h" 

#include <sol/sol.hpp>
#include "SFML/Graphics.hpp"

#include <string>

#include "componentsystems/MessagesComponentSystem.h" 
#include "managers/ScriptManager.h"
#include "objects/components/CollidesComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/tientities/TIEntity.h"
#include "utils/ComponentSystems.h"
#include "utils/TIEMath.h"

using namespace TIE;

CollidesComponentSystem::CollidesComponentSystem() {
	this->setName(CollidesComponentSystem::COLLIDES);

	ComponentSystems::insertComponentPropertyIntoMap(CollidesComponentSystem::IS_COLLIDABLE, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(CollidesComponentSystem::IS_COLLIDES, this->componentPropertyMap);

	this->hitboxCollisionMessageSubscription = MessagesComponentSystem::Instance()->registerMessageSubscription("HitboxCollision");
	this->traceCollisionMessageSubscription = MessagesComponentSystem::Instance()->registerMessageSubscription("TraceCollision");
}


void CollidesComponentSystem::update(const float delta) {
	// Two Pointer Technique
	for (std::list<Components>::iterator c1 = components.begin(), c2 = std::next(c1, 1); c2 != components.end(); ++c1, c2 = std::next(c1, 1)) {
		for (c2; c2 != components.end(); c2++) {
			this->checkHitboxCollisions(*c1, *c2);
			// this->checkTraceCollisions(*c1, *c2);
		}
	}
}


CollidesComponent& CollidesComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<CollidesComponent>()) {
        CollidesComponent& collidesComponent = tientity.addComponent<CollidesComponent>();
        PositionComponent& positionComponent = tientity.addComponent<PositionComponent>();
        this->components.push_back({ collidesComponent, positionComponent, tientity });
        return collidesComponent;
	} else {
		return *tientity.getComponent<CollidesComponent>();
	}
}


CollidesComponent& CollidesComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
	CollidesComponent& collidesComponent = this->addComponent(tientity);

	bool collidable  = ComponentSystems::getFactoryValue<bool>(factory, CollidesComponentSystem::IS_COLLIDABLE, collidesComponent.isCollidable(), tientity);
	collidesComponent.setCollidable(collidable);

	bool collides  = ComponentSystems::getFactoryValue<bool>(factory, CollidesComponentSystem::IS_COLLIDES, collidesComponent.isCollides(), tientity);
	collidesComponent.setCollides(collides);

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


void CollidesComponentSystem::setComponentProperty(const std::string& key, bool value, TIEntity& tientity)  {
	CollidesComponent& component = this->addComponent(tientity);
	if (key == CollidesComponentSystem::IS_COLLIDABLE) {
		component.setCollidable(value);
	} else if (key == CollidesComponentSystem::IS_COLLIDES) {
		component.setCollides(value);
	}
}


sol::object CollidesComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
	CollidesComponent* component = tientity.getComponent<CollidesComponent>();
	if (component) {
		if (key == CollidesComponentSystem::IS_COLLIDABLE) {
			return ScriptManager::Instance()->getObjectFromValue(component->isCollidable());
		} else if (key == CollidesComponentSystem::IS_COLLIDES) {
			return ScriptManager::Instance()->getObjectFromValue(component->isCollides());
		}
	}
	return ScriptManager::Instance()->getObjectFromValue(nullptr);
}


void CollidesComponentSystem::checkHitboxCollisions(Components& c1, Components& c2) {
	if (ComponentSystems::isDrawn(c1.tientity) && ComponentSystems::isDrawn(c2.tientity)) {
		sf::FloatRect c1Hitbox = ComponentSystems::getGlobalBounds(c1.tientity);
		sf::FloatRect c2Hitbox = ComponentSystems::getGlobalBounds(c2.tientity);
		if (c1Hitbox.intersects(c2Hitbox)) {
			// if (I want to know when I hit things && they want to say they got hit)
			if (c1.collidesComponent.isCollides() && c2.collidesComponent.isCollidable()) {
				MessagesComponentSystem::Instance()->sendMessage(
					this->hitboxCollisionMessageSubscription,
					c2.tientity.getId(), // sender
					c1.tientity.getId(), // reciepent
					ScriptManager::Instance()->getObjectFromValue(c2.tientity.getId()));
			}
			if (c2.collidesComponent.isCollides() && c2.collidesComponent.isCollidable()) {
				MessagesComponentSystem::Instance()->sendMessage(
					this->hitboxCollisionMessageSubscription,
					c1.tientity.getId(), // sender
					c2.tientity.getId(), // reciepent
					ScriptManager::Instance()->getObjectFromValue(c1.tientity.getId()));
			}
		}
	}
}
