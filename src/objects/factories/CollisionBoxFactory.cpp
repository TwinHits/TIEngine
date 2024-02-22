#include "objects/factories/tientities/CollisionBoxFactory.h"

#include "componentsystems/CollidesComponentSystem.h"
#include "componentsystems/MessagesComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/ShapeComponentSystem.h"
#include "managers/HashManager.h"
#include "templates/MakeUnique.h"

using namespace TIE;

CollisionBoxFactory::CollisionBoxFactory(TIEntity* parent): CollisionBoxFactory(*parent) {}


CollisionBoxFactory::CollisionBoxFactory(TIEntity& parent) {
    this->id = HashManager::Instance()->getNewGlobalId();
    this->setParent(parent);
}


const GlobalId CollisionBoxFactory::getId() {
    return this->id;
}


CollisionBoxFactory& CollisionBoxFactory::setParent(TIEntity& parent) {
    this->parent = &parent;
    return *this;
}


CollisionBoxFactory& CollisionBoxFactory::setPosition(const sf::Vector2f& position) {
    this->position = position;
    return *this;
}


CollisionBoxFactory& CollisionBoxFactory::setPosition(const float x, const float y) {
    this->position = sf::Vector2f(x, y);
    return *this;
}


CollisionBoxFactory& CollisionBoxFactory::setSize(const sf::Vector2f& size) {
    this->size = size;
    return *this;
}


CollisionBoxFactory& CollisionBoxFactory::setSize(const float width, const float height) {
    this->size = sf::Vector2f(width, height);
    return *this;
}


CollisionBoxFactory& CollisionBoxFactory::setRect(const sf::FloatRect& rect) {
    this->size = size;
    return *this;
}


CollisionBoxFactory& CollisionBoxFactory::setRect(const float x, const float y, const float width, const float height) {
    this->position = sf::Vector2f(x, y);
    this->size = sf::Vector2f(width, height);
    return *this;
}


TIEntity& CollisionBoxFactory::build() {
    TIEntity& collisionBox = this->parent->attachChild();
    collisionBox.setName(CollisionBoxFactory::COLLISION_BOX);

    MessagesComponent& messagesComponent = MessagesComponentSystem::Instance()->addComponent(collisionBox);
    messagesComponent.redirectFromId = this->parent->getId();
    messagesComponent.redirectToId = this->parent->getId();

    CollidesComponent& collidesComponent = CollidesComponentSystem::Instance()->addComponent(collisionBox);
    collidesComponent.setCollides(true);
    collidesComponent.setCollidable(true);
    collidesComponent.setPayload(this->parent->getId());

    PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(collisionBox);
    PositionComponentSystem::Instance()->setPosition(collisionBox, this->position);

    ShapeComponent& shapeComponent = ShapeComponentSystem::Instance()->addComponent(collisionBox);
    sf::RectangleShape& box = shapeComponent.addRectangleShape();
    box.setPosition(positionComponent.worldPosition);
    box.setSize(this->size);
    box.setOrigin(this->size.x / 2, this->size.y / 2);
    box.setFillColor(sf::Color::Transparent);
    shapeComponent.setRotates(false);
    shapeComponent.setDrawn(true);
    
    return collisionBox;
}
