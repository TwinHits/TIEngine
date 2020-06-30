#include "objects/components/MovesComponent.h"

using namespace TIE;

MovesComponent::MovesComponent() {

}

/*
void MovesComponentSystem::move(const float delta) {
	//float degrees = this->getRotation(); //Move according to current rotation
	float degrees = this->velocity.y; //Move according to velocity's rotation
	float x = 0;
	float y = 0;

	//Handle special values because of sin/cos handling the seminal values
	if (degrees == 0.0) {
		x = std::cos(ToRadians(degrees)) * this->velocity.x * delta;
	} else if (degrees == 90.0) {
		y = std::sin(ToRadians(degrees)) * this->velocity.x * delta;
	} else if (degrees == 180.0) {
		x = std::cos(ToRadians(degrees)) * this->velocity.x * delta;
	} else if (degrees == 270.0) {
		y = std::sin(ToRadians(degrees)) * this->velocity.x * delta;
	} else {
		x = std::cos(ToRadians(degrees)) * this->velocity.x * delta;
		y = std::sin(ToRadians(degrees)) * this->velocity.x * delta;
	}

    this->sf::Transformable::move(sf::Vector2f(x, y));
}
*/
