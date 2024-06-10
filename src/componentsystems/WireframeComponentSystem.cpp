#include "componentsystems/WireframeComponentSystem.h" 

#include <sol/sol.hpp>
#include "SFML/Graphics.hpp"

#include <string>

#include "componentsystems/LineComponentSystem.h"
#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/ShapeComponentSystem.h" 
#include "componentsystems/SpriteComponentSystem.h" 
#include "componentsystems/TextComponentSystem.h"
#include "managers/ComponentSystemsManager.h"
#include "managers/HashManager.h"
#include "managers/ScriptManager.h"
#include "objects/components/LineComponent.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/components/WireframeComponent.h"
#include "objects/tientities/TIEntity.h"
#include "utils/ComponentSystems.h"
#include "utils/TIEMath.h"

using namespace TIE;

WireframeComponentSystem::WireframeComponentSystem() {
	this->setName(WireframeComponentSystem::WIREFRAME);

	ComponentSystemsManager::Instance()->registerComponentPropertyKey(WireframeComponentSystem::SHOW_WIREFRAME, this);
}


void WireframeComponentSystem::update(const float delta) {
	for (auto& c : this->components) {
		if (c.wireframeComponent.getShowWireframe()) {
            SpriteComponent* spriteComponent = c.tientity.getComponent<SpriteComponent>();
            if (spriteComponent) {
				const std::pair<GlobalId, GlobalId>* wireframeShapeIds = c.wireframeComponent.getWireframeShapeIds(spriteComponent);
				if (wireframeShapeIds) {
					sf::Shape* sizeWireframeShape = c.shapeComponent.getShape(wireframeShapeIds->second);
					if (sizeWireframeShape) {
						sf::RectangleShape* rectangleShape = dynamic_cast<sf::RectangleShape*>(sizeWireframeShape);
						rectangleShape->setSize(sf::Vector2f(spriteComponent->getGlobalBounds().width, spriteComponent->getGlobalBounds().height));
						rectangleShape->setOrigin(sf::Vector2f(spriteComponent->getGlobalBounds().width / 2, spriteComponent->getGlobalBounds().height / 2));
					}
				}
            }

            TextComponent* textComponent = c.tientity.getComponent<TextComponent>();
            if (textComponent) {
				const std::pair<GlobalId, GlobalId>* wireframeShapeIds = c.wireframeComponent.getWireframeShapeIds(textComponent);
				if (wireframeShapeIds) {
					sf::Shape* sizeWireframeShape = c.shapeComponent.getShape(wireframeShapeIds->second);
					if (sizeWireframeShape) {
						sf::RectangleShape* rectangleShape = dynamic_cast<sf::RectangleShape*>(sizeWireframeShape);
						auto bounds = textComponent->getGlobalBounds();
						rectangleShape->setSize(sf::Vector2f(textComponent->getGlobalBounds().width, textComponent->getGlobalBounds().height));
					}
				}
            }

            LineComponent* lineComponent = c.tientity.getComponent<LineComponent>();
            if (lineComponent) {
				const std::pair<GlobalId, GlobalId>* wireframeShapeIds = c.wireframeComponent.getWireframeShapeIds(lineComponent);
				if (wireframeShapeIds) {
					sf::Shape* sizeWireframeShape = c.shapeComponent.getShape(wireframeShapeIds->second);
					if (sizeWireframeShape) {
						sf::RectangleShape* rectangleShape = dynamic_cast<sf::RectangleShape*>(sizeWireframeShape);
						rectangleShape->setSize(sf::Vector2f(lineComponent->getMagnitude(), 0));
					}
				}
            }

			MovesComponent* movesComponent = c.tientity.getComponent<MovesComponent>();
			if (movesComponent) {
				const std::pair<GlobalId, GlobalId>* wireframeShapeIds = c.wireframeComponent.getWireframeShapeIds(movesComponent);
				if (wireframeShapeIds) {
					sf::Shape* sizeWireframeShape = c.shapeComponent.getShape(wireframeShapeIds->second);
					if (sizeWireframeShape) {
						sf::RectangleShape* rectangleShape = dynamic_cast<sf::RectangleShape*>(sizeWireframeShape);
						PositionComponent* positionComponent = c.tientity.getComponent<PositionComponent>();
						if (movesComponent->hasTargetPosition() && positionComponent) {
							const sf::Vector2f& targetPosition = movesComponent->getTargetPosition();
							const float distanceToTargetPosition = Math::distanceBetweenTwoPoints(positionComponent->worldPosition, targetPosition);
							const float angleToTargetPosition = Math::angleBetweenTwoPoints(positionComponent->worldPosition, targetPosition);
							rectangleShape->setSize(sf::Vector2f(distanceToTargetPosition, 0));
							rectangleShape->setRotation(angleToTargetPosition);
						}
					}
				}
			}
		}
	}
}


WireframeComponent& WireframeComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<WireframeComponent>()) {
        WireframeComponent& wireframeComponent = tientity.addComponent<WireframeComponent>();
        ShapeComponent& shapeComponent = ShapeComponentSystem::Instance()->addComponent(tientity);
        this->components.push_back({ wireframeComponent, shapeComponent, tientity });
        return wireframeComponent;
	} else {
		return *tientity.getComponent<WireframeComponent>();
	}
}


WireframeComponent& WireframeComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
	WireframeComponent& wireframeComponent = this->addComponent(tientity);
	const ScriptTableReader& reader = factory.getReader().getReader(WireframeComponentSystem::WIREFRAME);

	bool showWireframe = reader.get<bool>(WireframeComponentSystem::SHOW_WIREFRAME, factory.getShowWireframe());
	wireframeComponent.setShowWireframe(showWireframe);

	if (wireframeComponent.getShowWireframe()) {
		SpriteComponent* spriteComponent = tientity.getComponent<SpriteComponent>();
		if (spriteComponent) {
			this->addWireframe(tientity, *spriteComponent);
		}

		TextComponent* textComponent = tientity.getComponent<TextComponent>();
		if (textComponent) {
			this->addWireframe(tientity, *textComponent);
		}

		LineComponent* lineComponent = tientity.getComponent<LineComponent>();
		if (lineComponent) {
			this->addWireframe(tientity, *lineComponent);
		}

		MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
		if (movesComponent) {
			this->addWireframe(tientity, *movesComponent);
		}
	}

	return wireframeComponent;
}


bool WireframeComponentSystem::removeComponent(TIEntity& tientity) {
	WireframeComponent* wireframeComponent = tientity.getComponent<WireframeComponent>();
	if (wireframeComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->wireframeComponent == wireframeComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<WireframeComponent>();
	} else {
		return false;
	}
}


void WireframeComponentSystem::setComponentProperty(const std::string& key, bool value, TIEntity& tientity)  {
	WireframeComponent& component = this->addComponent(tientity);
    if (key == WireframeComponentSystem::SHOW_WIREFRAME) {
        component.setShowWireframe(value);
        if (component.getShowWireframe()) {
            SpriteComponent* spriteComponent = tientity.getComponent<SpriteComponent>();
            if (spriteComponent) {
                this->addWireframe(tientity, *spriteComponent);
            }

            TextComponent* textComponent = tientity.getComponent<TextComponent>();
            if (textComponent) {
                this->addWireframe(tientity, *textComponent);
            }

            LineComponent* lineComponent = tientity.getComponent<LineComponent>();
            if (lineComponent) {
                this->addWireframe(tientity, *lineComponent);
            }

            MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
            if (movesComponent) {
                this->addWireframe(tientity, *movesComponent);
            }
		}
    }
}


sol::object WireframeComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
	WireframeComponent* component = tientity.getComponent<WireframeComponent>();
	return ScriptManager::Instance()->getObjectFromValue(nullptr);
}


bool WireframeComponentSystem::getShowWireframe(TIEntity& tientity) {
	WireframeComponent* component = tientity.getComponent<WireframeComponent>();
	return component && component->getShowWireframe();
}


void WireframeComponentSystem::addWireframe(TIEntity& tientity, SpriteComponent& spriteComponent) {
	WireframeComponent& wireframeComponent = this->addComponent(tientity);
	ShapeComponent& shapeComponent = ShapeComponentSystem::Instance()->addComponent(tientity);

    std::pair<GlobalId, GlobalId> wireframeShapeIds = SpriteComponentSystem::Instance()->addWireframe(tientity);
    wireframeComponent.addWireframeShapeIds(&spriteComponent, wireframeShapeIds);
	wireframeComponent.setShowWireframe(true);

	shapeComponent.setDrawn(true);
	shapeComponent.setRotates(true);
}


void WireframeComponentSystem::addWireframe(TIEntity& tientity, TextComponent& textComponent) {
	WireframeComponent& wireframeComponent = this->addComponent(tientity);
	ShapeComponent& shapeComponent = ShapeComponentSystem::Instance()->addComponent(tientity);

    std::pair<GlobalId, GlobalId> wireframeShapeIds = TextComponentSystem::Instance()->addWireframe(tientity);
    wireframeComponent.addWireframeShapeIds(&textComponent, wireframeShapeIds);
	wireframeComponent.setShowWireframe(true);

	shapeComponent.setDrawn(true);
	shapeComponent.setRotates(true);
}


void WireframeComponentSystem::addWireframe(TIEntity& tientity, LineComponent& lineComponent) {
	WireframeComponent& wireframeComponent = this->addComponent(tientity);
	ShapeComponent& shapeComponent = ShapeComponentSystem::Instance()->addComponent(tientity);

    std::pair<GlobalId, GlobalId> wireframeShapeIds = LineComponentSystem::Instance()->addWireframe(tientity);
    wireframeComponent.addWireframeShapeIds(&lineComponent, wireframeShapeIds);
	wireframeComponent.setShowWireframe(true);

	shapeComponent.setDrawn(true);
	shapeComponent.setRotates(true);
}


void WireframeComponentSystem::addWireframe(TIEntity& tientity, MovesComponent& movesComponent) {
	WireframeComponent& wireframeComponent = this->addComponent(tientity);
	ShapeComponent& shapeComponent = ShapeComponentSystem::Instance()->addComponent(tientity);

    std::pair<GlobalId, GlobalId> wireframeShapeIds = MovesComponentSystem::Instance()->addWireframe(tientity);
    wireframeComponent.addWireframeShapeIds(&movesComponent, wireframeShapeIds);
	wireframeComponent.setShowWireframe(true);

	shapeComponent.setDrawn(true);
	shapeComponent.setRotates(true);
}


std::pair<GlobalId, GlobalId> WireframeComponentSystem::createWireframe(TIEntity& tientity, const sf::FloatRect& bounds, const sf::Vector2f& origin) {
	return this->createWireframe(tientity, bounds, origin, 0);
}


std::pair<GlobalId, GlobalId> WireframeComponentSystem::createWireframe(TIEntity& tientity, const sf::FloatRect& bounds, const sf::Vector2f& origin, float rotation) {
	ShapeComponent& shapeComponent = ShapeComponentSystem::Instance()->addComponent(tientity);

	shapeComponent.setRotates(false);

	// Origin dot
	GlobalId originId = HashManager::Instance()->getNewGlobalId();
	sf::CircleShape& circleShape = shapeComponent.addCircleShape(originId);
	circleShape.setRadius(4.0f);
	circleShape.setOrigin(circleShape.getRadius(), circleShape.getRadius());
	circleShape.setFillColor(sf::Color::Blue);

	// Bounding box
	GlobalId boundsId = HashManager::Instance()->getNewGlobalId();
	sf::RectangleShape& rectangleShape = shapeComponent.addRectangleShape(boundsId);
	rectangleShape.setSize(sf::Vector2f(bounds.width, bounds.height));
	rectangleShape.setOrigin(origin);
	rectangleShape.setFillColor(sf::Color::Transparent);
	rectangleShape.setOutlineColor(sf::Color::Yellow);
	rectangleShape.setOutlineThickness(2);
	rectangleShape.setRotation(rotation);

	return std::pair<GlobalId, GlobalId>(originId, boundsId);
}
