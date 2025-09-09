#ifndef PATHSCOMPONENT_H
#define PATHSCOMPONENT_H

#include "objects/components/Component.h"

#include <queue>
#include <vector>

#include <SFML/Graphics.hpp>

#include "enumeration/PathStrategies.h"
#include "objects/GlobalId.h"

namespace TIE {

class PathsComponent : public Component {
    public:
		void setPathStrategy(const PathStrategies);
		const PathStrategies getPathStrategy();

		void setHasDestinationChanged(const bool);
		const bool isHasDestinationChanged();

		void setDestination(const sf::Vector2f&);
		void setDestination(const sf::Vector2i&);
		void setDestinationTIEntityId(const GlobalId);
		void setDestinationDistance(const float);

		const sf::Vector2f& getDestinaton();
		const GlobalId getDestinationTIEntityId();
		const float getDestinationDistance();

		void setSinglePositionPath(const sf::Vector2f&);
		void setPath(std::queue<sf::Vector2f>);
		void setPath(std::vector<sf::Vector2f>);
		void addPathNode(const sf::Vector2f&);

		const bool hasPath();
		const sf::Vector2f* const peekNextPathPosition();
		void popNextPathPosition();
		const bool isOnLastPathPosition();
	private:
		PathStrategies pathStrategy = PathStrategies::GOTO;

		std::queue<sf::Vector2f> path;
		bool hasDestinationChanged = false;

		sf::Vector2f destination = sf::Vector2f(0, 0);
		GlobalId destinationTIEntityId = 0;
		float destinationDistance = 0;
};

}

#endif
