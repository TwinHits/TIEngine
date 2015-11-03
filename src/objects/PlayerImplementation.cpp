#include "../managers/WindowManager.h"

#include "Player.h"

Player::Player(unsigned long id) 
{
	this->id = id;
}
Player::~Player() {}

unsigned long Player::getId() const { return id; }

Player::Player(const Player&) {}
void Player::operator=(const Player&) {}
