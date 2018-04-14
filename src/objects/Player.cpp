#include "managers/WindowManager.h"

#include "objects/Player.h"
#include "objects/GlobalId.h"

using namespace TIE;

Player::Player(GlobalId id)  {
	this->id = id;
}


Player::~Player() {

}


GlobalId Player::getId() const {
	return id; 
}


Player::Player(const Player&) {

}


void Player::operator=(const Player&) {

}