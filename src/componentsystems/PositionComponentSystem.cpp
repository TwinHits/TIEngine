#include "componentsystems/PositionComponentSystem.h"

#include <sstream>
#include <string>
#include <vector>

#include "objects/components/PositionComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/ScriptManager.h"
#include "utils/ComponentSystems.h"
#include "utils/TIEMath.h"

using namespace TIE;

PositionComponentSystem::PositionComponentSystem() {
    ComponentSystems::insertComponentPropertyIntoMap(PositionComponentSystem::ROTATION, this->componentPropertyMap);
    ComponentSystems::insertComponentPropertyIntoMap(PositionComponentSystem::ROTATES, this->componentPropertyMap);
    ComponentSystems::insertComponentPropertyIntoMap(PositionComponentSystem::POSITION_POSITION, this->componentPropertyMap);
    ComponentSystems::insertComponentPropertyIntoMap(PositionComponentSystem::POSITION_X, this->componentPropertyMap);
    ComponentSystems::insertComponentPropertyIntoMap(PositionComponentSystem::POSITION_Y, this->componentPropertyMap);
    ComponentSystems::insertComponentPropertyIntoMap(PositionComponentSystem::WORLD_POSITION, this->componentPropertyMap);
    ComponentSystems::insertComponentPropertyIntoMap(PositionComponentSystem::WORLD_ROTATION, this->componentPropertyMap);
}


void PositionComponentSystem::update(const float delta) {
    for (auto& c : this->components) {
        c.positionComponent.worldPosition = this->getWorldPosition(c.tientity);
        if (c.positionComponent.rotates) {
            c.positionComponent.worldRotation = this->getWorldRotation(c.tientity);
        }
    }
}


bool PositionComponentSystem::hasComponent(const TIEntity& tientity) {
    return tientity.hasComponent<PositionComponent>();
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

	float x = ComponentSystems::getFactoryValue<float>(factory, PositionComponentSystem::POSITION_X, positionComponent.position.x, tientity);
	float y = ComponentSystems::getFactoryValue<float>(factory, PositionComponentSystem::POSITION_Y, positionComponent.position.y, tientity);
	float rotation = ComponentSystems::getFactoryValue<float>(factory, PositionComponentSystem::ROTATION, positionComponent.rotation, tientity);
	bool rotates = ComponentSystems::getFactoryValue<bool>(factory, PositionComponentSystem::ROTATES, positionComponent.rotates, tientity);

    positionComponent.position.x = x;
    positionComponent.position.y = y;
    positionComponent.rotation = rotation;
    positionComponent.rotates = rotates;

    return positionComponent;
}


bool PositionComponentSystem::setComponentProperty(const std::string& key, bool value, TIEntity& tientity) {
    return false;
}


bool PositionComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity) {
    PositionComponent* component = tientity.getComponent<PositionComponent>();
    if (component != nullptr) {
        if (key == PositionComponentSystem::ROTATION) {
            component->rotation = value;
        } else if (key == PositionComponentSystem::POSITION_X) {
            component->position.x = value;
        } else if (key == PositionComponentSystem::POSITION_Y) {
            component->position.y = value;
        }
    }
    return false;
}


bool PositionComponentSystem::setComponentProperty(const std::string& key, const sf::Vector2f& value, TIEntity& tientity) {
    PositionComponent* component = tientity.getComponent<PositionComponent>();
    if (component != nullptr) {
        if (key == PositionComponentSystem::POSITION_POSITION) {
            component->position = value;
        }
    }
    return false;
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


const std::string& PositionComponentSystem::getName() {
    return PositionComponentSystem::POSITION;
}


void PositionComponentSystem::setPosition(TIEntity& tientity, float x, float y) {
    PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
    if (positionComponent != nullptr) {
        positionComponent->position.x = x;
        positionComponent->position.y = y;
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
    return Math::distanceBetweenTwoPoints(position1.position, position2.position) <= range;
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

