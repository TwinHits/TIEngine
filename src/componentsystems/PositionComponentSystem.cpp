#include "componentsystems/PositionComponentSystem.h"

#include <sstream>
#include <string>
#include <vector>

#include "objects/components/PositionComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "managers/ComponentSystemsManager.h"
#include "managers/ScriptManager.h"
#include "utils/ComponentSystems.h"
#include "utils/TIEMath.h"

using namespace TIE;

PositionComponentSystem::PositionComponentSystem() {
    this->setName(PositionComponentSystem::POSITION);
    ComponentSystemsManager::Instance()->registerComponentPropertyKey(PositionComponentSystem::ROTATION, this);
    ComponentSystemsManager::Instance()->registerComponentPropertyKey(PositionComponentSystem::ROTATES, this);
    ComponentSystemsManager::Instance()->registerComponentPropertyKey(PositionComponentSystem::POSITION_POSITION, this);
    ComponentSystemsManager::Instance()->registerComponentPropertyKey(PositionComponentSystem::POSITION_X, this);
    ComponentSystemsManager::Instance()->registerComponentPropertyKey(PositionComponentSystem::POSITION_Y, this);
    ComponentSystemsManager::Instance()->registerComponentPropertyKey(PositionComponentSystem::WORLD_POSITION, this);
    ComponentSystemsManager::Instance()->registerComponentPropertyKey(PositionComponentSystem::WORLD_ROTATION, this);
}


void PositionComponentSystem::update(const float delta) {
    for (auto& c : this->components) {
        this->updateWorldCoordinates(c.positionComponent, c.tientity);
    }
}


PositionComponent& PositionComponentSystem::addComponent(TIEntity& tientity) {
    if (!tientity.hasComponent<PositionComponent>()) {
        PositionComponent& positionComponent = tientity.addComponent<PositionComponent>();
        this->components.push_back({ positionComponent, tientity });
        return positionComponent;
    } else {
        return *tientity.getComponent<PositionComponent>();
    }
}


PositionComponent& PositionComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
    PositionComponent& positionComponent = this->addComponent(tientity);
    const ScriptTableReader& reader = factory.getReader().getReader(PositionComponentSystem::POSITION);

	const float& x = reader.get<float>(PositionComponentSystem::POSITION_X, positionComponent.position.x);
    positionComponent.position.x = x;

	const float& y = reader.get<float>(PositionComponentSystem::POSITION_Y, positionComponent.position.y);
    positionComponent.position.y = y;

	const float& rotation = reader.get<float>(PositionComponentSystem::ROTATION, positionComponent.rotation);
    positionComponent.rotation = Math::normalizeAngleDegrees(rotation);

	const bool& rotates = reader.get<bool>(PositionComponentSystem::ROTATES, positionComponent.rotates);
    positionComponent.rotates = rotates;

    this->updateWorldCoordinates(positionComponent, tientity);

    return positionComponent;
}


void PositionComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity) {
    PositionComponent& component = PositionComponentSystem::addComponent(tientity);
    if (key == PositionComponentSystem::ROTATION) {
        component.rotation = value;
        this->updateWorldCoordinates(component, tientity);
    } else if (key == PositionComponentSystem::POSITION_X) {
        component.position.x = value;
        this->updateWorldCoordinates(component, tientity);
    } else if (key == PositionComponentSystem::POSITION_Y) {
        component.position.y = value;
        this->updateWorldCoordinates(component, tientity);
    }
}


void PositionComponentSystem::setComponentProperty(const std::string& key, const sf::Vector2f& value, TIEntity& tientity) {
    PositionComponent& component = PositionComponentSystem::addComponent(tientity);
    if (key == PositionComponentSystem::POSITION_POSITION) {
        component.position = value;
        this->updateWorldCoordinates(component, tientity);
    }
}


sol::object PositionComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
    PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
    if (positionComponent != nullptr) {
        if (key == PositionComponentSystem::POSITION_POSITION) {
            return ScriptManager::Instance()->getObjectFromValue<sf::Vector2f>(positionComponent->position);
        } else if (key == PositionComponentSystem::WORLD_POSITION) {
            return ScriptManager::Instance()->getObjectFromValue<sf::Vector2f>(positionComponent->worldPosition);
        } else if (key == PositionComponentSystem::ROTATES) {
            return ScriptManager::Instance()->getObjectFromValue(positionComponent->rotates);
        } else if (key == PositionComponentSystem::ROTATION) {
            return ScriptManager::Instance()->getObjectFromValue(positionComponent->rotation);
        } else if (key == PositionComponentSystem::WORLD_ROTATION) {
            return ScriptManager::Instance()->getObjectFromValue(positionComponent->worldRotation);
        }
    }
    return ScriptManager::Instance()->getObjectFromValue(nullptr);
}


bool PositionComponentSystem::removeComponent(TIEntity& tientity) {
	PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
	if (positionComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->positionComponent == positionComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<PositionComponent>();
	} else {
		return false;
	}
}


void PositionComponentSystem::setPosition(TIEntity& tientity, const sf::Vector2f& position) {
    this->setPosition(tientity, position.x, position.y);
}


void PositionComponentSystem::setPosition(TIEntity& tientity, const float x, const float y) {
    PositionComponent& positionComponent = this->addComponent(tientity);
    positionComponent.position.x = x;
    positionComponent.position.y = y;
    this->updateWorldCoordinates(positionComponent, tientity);
}


void PositionComponentSystem::setRotation(TIEntity& tientity, const float rotation) {
    PositionComponent& positionComponent = this->addComponent(tientity);
    positionComponent.rotation = rotation;
    this->updateWorldCoordinates(positionComponent, tientity);
}


void PositionComponentSystem::updateWorldCoordinates(TIEntity& tientity) {
    if (tientity.hasComponent<PositionComponent>()) {
        this->updateWorldCoordinates(*tientity.getComponent<PositionComponent>(), tientity);
    }
}


void PositionComponentSystem::updateWorldCoordinates(PositionComponent& positionComponent, TIEntity& tientity) {
    positionComponent.worldPosition = this->getWorldPosition(tientity);
    if (positionComponent.rotates) {
        positionComponent.worldRotation = this->getWorldRotation(tientity);
    }
}


sf::Vector2f PositionComponentSystem::getWorldPosition(TIEntity& tientity) {
    sf::Vector2f worldPosition = sf::Vector2f();

    for (TIEntity* t = &tientity; t != nullptr; t = &t->getParent()) {
        PositionComponent* component = t->getComponent<PositionComponent>();
        if (component != nullptr) {
            PositionComponent* parentComponent = t->getParent().getComponent<PositionComponent>();
            if (parentComponent != nullptr && component->rotates) {
                // If the parent has a position, then rotate the child's position by the parent's rotation to stay oriented around parent's origin
                worldPosition += Math::rotateVectorByAngle(component->position, parentComponent->rotation);
            } else { 
                worldPosition += component->position;
            }
        }
    }

    return worldPosition;
}


float PositionComponentSystem::getWorldRotation(TIEntity& tientity) {
    float rotation = 0;

    for (TIEntity* t = &tientity; t != nullptr; t = &t->getParent()) {
        PositionComponent* component = t->getComponent<PositionComponent>();
        if (component != nullptr) {
            rotation += component->rotation;
        }
    }

    return rotation;
}


sf::Transform PositionComponentSystem::getWorldTransform(TIEntity& tientity) {
    sf::Transform transform = sf::Transform::Identity;

    for (TIEntity* t = &tientity; t != nullptr; t = &t->getParent()) {
        SpriteComponent* component = t->getComponent<SpriteComponent>();
        if (component != nullptr) {
            transform *= component->getTransform();
        }
    }

    return transform;
}


bool PositionComponentSystem::arePositionsInRange(PositionComponent& position1, PositionComponent& position2, const float range) {
    return Math::distanceBetweenTwoPoints(position1.worldPosition, position2.worldPosition) <= range;
}


std::vector<TIEntity*> PositionComponentSystem::findTIEntitiesWithinRange(TIEntity& source, const float distance, TIEntity& searchRoot) {
    std::vector<TIEntity*> tientitiesWithinDistance;
    return PositionComponentSystem::findTIEntitiesWithinRange(source, distance, searchRoot, tientitiesWithinDistance);
}


std::vector<TIEntity*> PositionComponentSystem::findTIEntitiesWithinRange(TIEntity& source, const float distance, TIEntity& searchRoot, std::vector<TIEntity*>& tientitiesWithinDistance) {
    PositionComponent* sourceComponent = source.getComponent<PositionComponent>();
    if (sourceComponent != nullptr) {
        for (auto& child : searchRoot.getChildren()) {
            if (child->isSceneLayer()) {
                PositionComponentSystem::findTIEntitiesWithinRange(source, distance, *child.get(), tientitiesWithinDistance);
            } else if (child->getId() != source.getId()) {
                PositionComponent* childComponent = child->getComponent<PositionComponent>();
                if (childComponent != nullptr) {
                    if (PositionComponentSystem::arePositionsInRange(*sourceComponent, *childComponent, distance)) {
                        tientitiesWithinDistance.push_back(child.get());
                    };
                }
            }
        };
    }
    return tientitiesWithinDistance;
}

