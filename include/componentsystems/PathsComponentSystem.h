#ifndef PATHSCOMPONENTSYSTEM_H
#define PATHSCOMPONENTSYSTEM_H

#include "componentSystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <map>
#include <memory>

#include "objects/components/PathsComponent.h"
#include "objects/components/PositionComponent.h"

#include "componentsystems/strategies/paths/PathsStrategy.h"

namespace TIE {

class PathsComponentSystem : public Singleton<PathsComponentSystem>, public OwnsComponent<PathsComponent> {
	public:
		PathsComponentSystem();
		void update(const float);
		PathsComponent& addComponent(TIEntity&);
		PathsComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);

		void setComponentProperty(const std::string&, float, TIEntity&);
		void setComponentProperty(const std::string&, const sf::Vector2f&, TIEntity&);
		void setComponentProperty(const std::string&, const std::vector<sf::Vector2f>&, TIEntity&);
		void setComponentProperty(const std::string&, const sf::Vector2i&, TIEntity&);

		sol::object getComponentProperty(const std::string& key, TIEntity& tientity);

		std::pair<GlobalId, GlobalId> addWireframe(TIEntity& tientity);
		static const inline std::string PATHS = "paths";
		static const inline std::string DESTINATION = "destination";
		static const inline std::string DESTINATION_PATH = "destination_path";
		static const inline std::string DESTINATION_X = "destination_x";
		static const inline std::string DESTINATION_Y = "destination_y";
		static const inline std::string AT_DESTINATION = "atDestination";
		static const inline std::string STRATEGY = "strategy";

	private:
		struct Components {
			PathsComponent& pathsComponent;
			PositionComponent& positionComponent;
			TIEntity& tientity;
		};
		std::list<Components> components;

		std::map<PathStrategies, std::unique_ptr<PathStrategy>> pathStrategies;
		std::map<std::string, PathStrategies> pathStrategiesByName;

		void initializePathStrategies();
};

}
#endif
