#include "componentsystems/ShapeComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "componentsystems/PositionComponentSystem.h"
#include "objects/components/ShapeComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/tientities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/AssetsManager.h"
#include "managers/ScriptManager.h"
#include "utils/StringHelpers.h"

using namespace TIE;

ShapeComponentSystem::ShapeComponentSystem() {
	this->setName(ShapeComponentSystem::SHAPE);
}


void ShapeComponentSystem::update(const float delta) {
	for (auto& c : this->components) {
		for (auto& s : c.shapeComponent.getShapes()) {
			s->setPosition(c.positionComponent.worldPosition);
			s->setRotation(c.positionComponent.worldRotation);
		}
	}
}


ShapeComponent& ShapeComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
	return this->addComponent(tientity);
}


ShapeComponent& ShapeComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<ShapeComponent>()) {
		ShapeComponent& shapeComponent = tientity.addComponent<ShapeComponent>();
		PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);
		this->components.push_back({ shapeComponent, positionComponent, tientity });
		return shapeComponent;
	} else {
		return *tientity.getComponent<ShapeComponent>();
	}

}


bool ShapeComponentSystem::removeComponent(TIEntity& tientity) {
	ShapeComponent* shapeComponent = tientity.getComponent<ShapeComponent>();
	if (shapeComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->shapeComponent == shapeComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<ShapeComponent>();
	} else {
		return false;
	}
}


void ShapeComponentSystem::addWireframe(TIEntity& tientity, const SpriteComponent& component) {
	this->createWireframe(tientity, component.getLocalBounds(), component.getOrigin());
}


void ShapeComponentSystem::addWireframe(TIEntity& tientity, const TextComponent& component) {
	this->createWireframe(tientity, component.getLocalBounds(), component.getOrigin());
}

ShapeComponent& ShapeComponentSystem::createWireframe(TIEntity& tientity, const sf::FloatRect& bounds, const sf::Vector2f& origin) {
	ShapeComponent& shapeComponent = this->addComponent(tientity);

	// Bounding box
	sf::RectangleShape& rectangleShape = shapeComponent.addRectangleShape();
	rectangleShape.setSize(sf::Vector2f(bounds.left + bounds.width, bounds.top + bounds.height));
	rectangleShape.setOrigin(origin);
	rectangleShape.setFillColor(sf::Color::Transparent);
	rectangleShape.setOutlineColor(sf::Color::Yellow);
	rectangleShape.setOutlineThickness(2);

	// Origin dot
	sf::CircleShape& circleShape = shapeComponent.addCircleShape();
	circleShape.setRadius(2.0f);
	circleShape.setOrigin(circleShape.getRadius(), circleShape.getRadius());
	circleShape.setFillColor(sf::Color::Blue);
	
	return shapeComponent;
}
