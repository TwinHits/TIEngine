#include "Player.h"

Player::Player(int id) 
{
	this->id = id;
}

int Player::getId() const { return id; }

Player::~Player() {}
Player::Player(const Player&) {}
void Player::operator=(const Player&) {}
