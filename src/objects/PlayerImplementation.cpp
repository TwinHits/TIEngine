#include "../managers/WindowManager.h"

#include "Player.h"
#include "GlobalId.h"

Player::Player(GlobalId id) 
{
	this->id = id;
}
Player::~Player() {}

GlobalId Player::getId() const { return id; }

Player::Player(const Player&) {}
void Player::operator=(const Player&) {}
