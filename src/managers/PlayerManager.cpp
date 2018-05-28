#include "managers/PlayerManager.h"
#include "managers/HashManager.h"
#include "managers/LogManager.h"
#include "managers/ViewManager.h"

#include "templates/MakeUnique.h"

using namespace TIE;

PlayerManager::PlayerManager() {

}


PlayerManager::~PlayerManager() {

}


Player& PlayerManager::addPlayer() {
	GlobalId id = HashManager::Instance()->getNewGlobalId();
	sf::View& view = TIE::ViewManager::Instance()->getActiveView();
	if (players.find(id) == players.end()) {
		players[id] = make_unique<Player>(id, view);
		LogManager::Instance()->logInfo("Added player '" + std::to_string(id) + "'.");
		return *players[id];
	}
	else {
		LogManager::Instance()->logWarn("Hash collison! Player '" + std::to_string(id) + "' already exists, recursively rehashing.");
		return addPlayer();
	}	
}

 Player& PlayerManager::addPlayer(std::unique_ptr<Player> player) {
	GlobalId id = player->getId();
	if (players.find(id) == players.end()) {
		players[id] = std::move(player);
		LogManager::Instance()->logInfo("Added player '" + std::to_string(id) + "'.");
		return *players[id];
	}
	else {
		LogManager::Instance()->logWarn("Player '" + std::to_string(id) + "' already exists, returning that player.");
		return *players[id];
	}	
}


void PlayerManager::rmPlayer(GlobalId id) {
	auto player = players.find(id);
	if (player != players.end()) {
		players.erase(player);	
		LogManager::Instance()->logInfo("Deleted player '" + std::to_string(id) + "'.");
	}
	else {
		LogManager::Instance()->logWarn("Player '" + std::to_string(id) + "' does not exist, doing nothing.");
	}
}


 Player& PlayerManager::getPlayer(GlobalId id) {
	if (players.find(id) != players.end()) {
		return *players[id];
	}
	else {
		LogManager::Instance()->logError("Player '" + std::to_string(id) + "' does not exist, segfaulting.");
		return *players[id];
	}
}


const std::map<GlobalId, std::unique_ptr<Player> >& PlayerManager::getAllPlayers() {
	return players;
}


void PlayerManager::registerId(std::string key, GlobalId id) {
	this->registeredIds[key] = id;
}


GlobalId PlayerManager::getRegisteredId(std::string key) {
	return this->registeredIds[key];

}
