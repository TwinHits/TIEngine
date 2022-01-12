#include "componentsystems/ShapeComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "componentsystems/PositionComponentSystem.h"
#include "objects/components/ShapeComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/AssetsManager.h"
#include "utils/StringHelpers.h"

using namespace TIE;

void ShapeComponentSystem::update(const float delta) {
	for (auto& c : this->components) {
		for (auto& s : c.shapeComponent.getShapes()) {
			s->setPosition(PositionComponentSystem::Instance()->getWorldPosition(c.tientity));
			s->setRotation(PositionComponentSystem::Instance()->getWorldRotation(c.tientity));
		}
	}
}


void ShapeComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
}

ShapeComponent& ShapeComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<ShapeComponent>()) {
		ShapeComponent& shapeComponent = tientity.addComponent<ShapeComponent>();
		PositionComponent& positionComponent = tientity.addComponent<PositionComponent>();
		Components components = { shapeComponent, positionComponent, tientity };
		this->components.push_back(components);
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


const std::string& ShapeComponentSystem::getName() {
	return ShapeComponentSystem::SHAPE;
}


void ShapeComponentSystem::addWireframe(TIEntity& tientity) {
	ShapeComponent& shapeComponent = this->addComponent(tientity);
	SpriteComponent& spriteComponent = *tientity.getComponent<SpriteComponent>();
	sf::RectangleShape& rectangleShape = shapeComponent.addRectangleShape();
	sf::Vector2f textureSize = sf::Vector2f(spriteComponent.getTexture()->getSize());
	rectangleShape.setSize(textureSize);
	rectangleShape.setOrigin(textureSize.x / 2, textureSize.y / 2);
	rectangleShape.setFillColor(sf::Color::Transparent);
	rectangleShape.setOutlineColor(sf::Color::Yellow);
	rectangleShape.setOutlineThickness(2);
}
