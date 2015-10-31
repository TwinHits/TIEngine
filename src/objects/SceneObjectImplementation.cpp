#include "SceneObject.h"

SceneObject::SceneObject() {}
SceneObject::SceneObject(const SceneObject&) {}
SceneObject::~SceneObject() {}
void SceneObject::operator=(const SceneObject&) {}

void SceneObject::setDraw(bool b) { draw = b; }

const sf::Sprite& SceneObject::getSprite() { return sprite; }

