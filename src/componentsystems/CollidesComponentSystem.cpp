#include "componentsystems/CollidesComponentSystem.h" 

#include <sol/sol.hpp>
#include "SFML/Graphics.hpp"

#include <string>

#include "componentsystems/MessagesComponentSystem.h" 
#include "managers/ComponentSystemsManager.h"
#include "managers/MessageManager.h"
#include "managers/ScriptManager.h"
#include "objects/components/CollidesComponent.h"
#include "objects/components/LineComponent.h"
#include "objects/tientities/TIEntity.h"
#include "utils/ComponentSystems.h"
#include "utils/TIEMath.h"

using namespace TIE;

CollidesComponentSystem::CollidesComponentSystem() {
	this->setName(CollidesComponentSystem::COLLIDES);

	ComponentSystemsManager::Instance()->registerComponentPropertyKey(CollidesComponentSystem::IS_COLLIDABLE, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(CollidesComponentSystem::IS_COLLIDES, this);

	this->collisionMessageSubscription = MessageManager::Instance()->getSubscriptionId("Collision");
}


void CollidesComponentSystem::update(const float delta) {
	// Two Pointer Technique
	if (components.size() >= 2) {
		for (std::list<Components>::iterator c1 = components.begin(), c2 = std::next(c1, 1); c2 != components.end(); ++c1, c2 = std::next(c1, 1)) {
			for (c2; c2 != components.end(); c2++) {
				if (!c1->tientity.isRelatedTo(c2->tientity)) {
					this->checkHitboxCollisions(*c1, *c2);
                    this->checkLineCollisions(*c1, *c2);
                    this->checkLineCollisions(*c2, *c1);
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
	const ScriptTableReader& reader = factory.getReader().getReader(CollidesComponentSystem::COLLIDES);

	const bool& collidable  = reader.get<bool>(CollidesComponentSystem::IS_COLLIDABLE, collidesComponent.isCollidable());
	collidesComponent.setCollidable(collidable);

	const bool& collides = reader.get<bool>(CollidesComponentSystem::IS_COLLIDES, collidesComponent.isCollides());
	collidesComponent.setCollides(collides);

	const GlobalId& payload = tientity.getId();
	collidesComponent.setPayload(payload);

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
		const sf::FloatRect& c1Hitbox = ComponentSystems::getGlobalBounds(c1.tientity);
		const sf::FloatRect& c2Hitbox = ComponentSystems::getGlobalBounds(c2.tientity);
		if (c1Hitbox.intersects(c2Hitbox)) {
			// if (I want to know when I hit things && they want to say they got hit)
			if (c1.collidesComponent.isCollides() && c2.collidesComponent.isCollidable()) {
				MessagesComponentSystem::Instance()->sendMessage({
					this->collisionMessageSubscription,
					c2.tientity.getId(), // sender
					c1.tientity.getId(), // recipient
					ScriptManager::Instance()->getObjectFromValue(c2.collidesComponent.getPayload())
				});
			}
			if (c2.collidesComponent.isCollides() && c2.collidesComponent.isCollidable()) {
				MessagesComponentSystem::Instance()->sendMessage({
					this->collisionMessageSubscription,
					c1.tientity.getId(), // sender
					c2.tientity.getId(), // recipient
					ScriptManager::Instance()->getObjectFromValue(c1.collidesComponent.getPayload()) 
				});
			}
		}
	}
}


void CollidesComponentSystem::checkLineCollisions(Components& lineComponents, Components& hitboxComponents) {
	if (lineComponents.tientity.hasComponent<LineComponent>() && ComponentSystems::isDrawn(hitboxComponents.tientity)) {
        // if (I want to know when I hit things && they want to say they got hit)
        if (lineComponents.collidesComponent.isCollides() && hitboxComponents.collidesComponent.isCollidable()) {
            const sf::VertexArray& line = lineComponents.tientity.getComponent<LineComponent>()->getLine();
            const sf::FloatRect& c2Hitbox = ComponentSystems::getGlobalBounds(hitboxComponents.tientity);
			if (Math::doesLineIntersectRect(line, c2Hitbox)) {
				MessagesComponentSystem::Instance()->sendMessage({
					this->collisionMessageSubscription,
					hitboxComponents.tientity.getId(), // sender
					lineComponents.tientity.getId(), // recipient
					ScriptManager::Instance()->getObjectFromValue(hitboxComponents.collidesComponent.getPayload())
				});
            }
		}
	}
}
