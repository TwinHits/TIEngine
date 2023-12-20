#ifndef COMPONENTSYSTEM_H
#define COMPONENTSYSTEM_H

#include <string>

#include "objects/factories/tientities/TIEntityFactory.h"
#include "objects/tientities/TIEntity.h"
#include "utils/ComponentSystems.h"
#include "utils/types/ComponentSystemsTypes.h"

namespace TIE {

class ComponentSystem {
    public:
        ComponentSystem() {};
        virtual ~ComponentSystem() {};

		virtual void update(const float) = 0;
		virtual const std::string& getName();
		void addPropertyToComponentPropertyMap(const std::string&);

		virtual bool hasComponent(const TIEntity&) = 0;
		virtual Component& addComponent(TIEntity&) = 0;
		virtual Component& addComponent(const TIEntityFactory&, TIEntity&) = 0;
		virtual bool removeComponent(TIEntity&) = 0;
		
		virtual void setComponentProperty(const std::string&, bool, TIEntity&);
		virtual void setComponentProperty(const std::string&, float, TIEntity&);
		virtual void setComponentProperty(const std::string&, const std::string&, TIEntity&);
		virtual void setComponentProperty(const std::string&, const sf::Vector2f&, TIEntity&);
		virtual void setComponentProperty(const std::string&, const sf::Vector2i&, TIEntity&);
		virtual sol::object getComponentProperty(const std::string&, TIEntity&);

		virtual ComponentSystems::ComponentSystemPropertiesMap& populateComponentSystemsPropertiesMap(ComponentSystems::ComponentSystemPropertiesMap&);
		virtual std::string getComponentPropertiesString(TIEntity& tientity);

    protected:
		void setName(const std::string&);
		std::string name = "";
        ComponentSystems::ComponentSystemPropertyMap componentPropertyMap;

};

}

#endif
