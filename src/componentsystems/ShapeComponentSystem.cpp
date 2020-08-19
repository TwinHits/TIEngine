#include "componentsystems/ShapeComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/ShapeComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/AssetsManager.h"
#include "utilities/StringHelpers.h"

using namespace TIE;

void ShapeComponentSystem::update(TIEntity& tientity, const float delta) {

}


ShapeComponent& ShapeComponentSystem::addComponent(TIEntity& entity) {
	return entity.addComponent<ShapeComponent>();
}


void ShapeComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& entity) {
	this->addComponent(entity);
}

/*
sf::Transform GraphicsComponentSystem::getWorldTransform() const {
	sf::Transform transform = sf::Transform::Identity;

	for (const TIEntity* n = this; n != nullptr; n = n->parent) {
		transform = n->getTransform() * transform;
	}

	return transform;
}


sf::Vector2f GraphicsComponentSystem::getWorldPosition() const {
	return this->getWorldTransform() * sf::Vector2f();
}

float GraphicsComponentSystem::getWorldRotation() const {
	float rotation = 0;

	for (SceneNode* n = parent; n != nullptr; n = n->parent) {
		rotation += n->getRotation();
	}

	rotation += this->getRotation();

	return rotation;
}
*/
