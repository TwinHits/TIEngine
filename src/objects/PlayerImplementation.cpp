#include "../managers/WindowManager.h"

#include "Player.h"

Player::Player(int id) 
{
	this->id = id;
	window = &WindowManager::Instance()->addWindow();
}

int Player::getId() const { return id; }
sf::RenderWindow& Player::getWindow() const { return *window; }

Player::~Player() {}
Player::Player(const Player&) {}
void Player::operator=(const Player&) {}
