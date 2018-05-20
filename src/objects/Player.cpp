#include "managers/HashManager.h"

#include "objects/Player.h"
#include "objects/GlobalId.h"

using namespace TIE;

Player::Player(GlobalId id)  {
	this->id = id;
}

Player::Player()  {
	this->id = HashManager::Instance()->getNewGlobalId();
}


Player::~Player() {

}


GlobalId Player::getId() const {
	return id; 
}
