#ifndef COMPONENTSYSTEM_H
#define COMPONENTSYSTEM_H

#include <string>

#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "utils/types/ComponentSystemsTypes.h"

namespace TIE {

class ComponentSystem {
	public:
		virtual ~ComponentSystem() {};
		virtual void update(const float) = 0;
		virtual Component& addComponent(TIEntity&) = 0;
		virtual Component& addComponent(const TIEntityFactory&, TIEntity&) = 0;
		virtual bool removeComponent(TIEntity&) = 0;
		virtual const std::string& getName() = 0;
		virtual bool setComponentProperty(const std::string&, bool, TIEntity&);
		virtual bool setComponentProperty(const std::string&, float, TIEntity&);
		virtual bool setComponentProperty(const std::string&, const std::string&, TIEntity&);
		virtual bool setComponentProperty(const std::string&, const sf::Vector2f&, TIEntity&);
		virtual bool setComponentProperty(const std::string&, const sf::Vector2i&, TIEntity&);
		virtual sol::object getComponentProperty(const std::string&, TIEntity&) = 0;
		virtual ComponentSystems::ComponentSystemPropertiesMap& populateComponentSystemsPropertiesMap(ComponentSystems::ComponentSystemPropertiesMap&);
};

}
#endif