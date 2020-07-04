#include "objects/Player.h"

#include "managers/HashManager.h"
#include "objects/GlobalId.h"

using namespace TIE;

Player::Player(GlobalId id, sf::View& view) :
	view(view) {
	this->id = id;
}

Player::Player(sf::View& view) : 
	view(view) {
	Player(HashManager::Instance()->getNewGlobalId(), view);
}


Player::~Player() {

}


GlobalId Player::getId() const {
	return id; 
}


void Player::setView(sf::View& view) {
	this->view = view;
}

sf::View& Player::getView() {
	return this->view;
}
