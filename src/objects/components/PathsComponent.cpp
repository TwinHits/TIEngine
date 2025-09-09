#include "objects/components/PathsComponent.h"

using namespace TIE;

void PathsComponent::setPath(std::queue<sf::Vector2f> path) {
    this->path.swap(path);
};


void PathsComponent::setPath(std::vector<sf::Vector2f> path) {
    this->path.swap(std::queue<sf::Vector2f>());
    for (auto& position : path) {
        this->path.push(position);
    }
};


void PathsComponent::setPathStrategy(const PathStrategies pathStrategy) {
    this->pathStrategy = pathStrategy;

}

const PathStrategies PathsComponent::getPathStrategy() {
    return this->pathStrategy;
}


void PathsComponent::setHasDestinationChanged(const bool hasDestinationChanged) {
    this->hasDestinationChanged = hasDestinationChanged;
}


const bool PathsComponent::isHasDestinationChanged() {
    return this->hasDestinationChanged;
}


void PathsComponent::setDestination(const sf::Vector2i& destination) {
    this->destination = sf::Vector2f(destination);
    this->hasDestinationChanged = true;
}


void PathsComponent::setDestination(const sf::Vector2f& destination) {
    this->destination = destination;
    this->hasDestinationChanged = true;
}


void PathsComponent::setDestinationTIEntityId(const GlobalId destinationTIEntityId) {
    this->destinationTIEntityId = destinationTIEntityId;
    this->hasDestinationChanged = true;
}


void PathsComponent::setDestinationDistance(const float distance) {
    this->destinationDistance = distance;
    this->hasDestinationChanged = true;
}

const sf::Vector2f& PathsComponent::getDestinaton() {
    return this->destination;
}

const GlobalId PathsComponent::getDestinationTIEntityId() {
    return this->destinationTIEntityId;
}

const float PathsComponent::getDestinationDistance() {
    return this->destinationDistance;
}


void PathsComponent::setSinglePositionPath(const sf::Vector2f& position) {
    this->path.swap(std::queue<sf::Vector2f>({ position }));
};


const bool PathsComponent::hasPath() {
    return !this->path.empty();
};


const sf::Vector2f* const PathsComponent::peekNextPathPosition() {
    if (!this->path.empty()) {
        return &this->path.front();
    } else {
        return nullptr;
    }
};


void PathsComponent::popNextPathPosition() {
    if (!this->path.empty()) {
        this->path.pop();
    }
};


const bool PathsComponent::isOnLastPathPosition() {
    return this->path.size() == 1;
};


void PathsComponent::addPathNode(const sf::Vector2f& node) {
    this->path.push(node);
};
