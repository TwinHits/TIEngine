#ifndef TEXTCOMPONENTSYSTEM_H
#define TEXTCOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/TextComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"

namespace TIE {

class TextComponentSystem : public Singleton<TextComponentSystem>, public ComponentSystem {
	public:
		TextComponentSystem() {};
		void update(const float);
		void addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);
		const std::string& getName();

		bool setComponentProperty(const std::string&, bool, TIEntity&);
		bool setComponentProperty(const std::string&, float, TIEntity&);
		bool setComponentProperty(const std::string&, const std::string&, TIEntity&);
		sol::object getComponentProperty(const std::string&, TIEntity&);
		ComponentSystems::ComponentSystemPropertiesMap& populateComponentSystemsPropertiesMap(ComponentSystems::ComponentSystemPropertiesMap&);

		static void setOriginForTextAlignment(TextComponent&);

		static const inline std::string TEXT = "text";
		static const inline std::string DRAWN = "text.drawn";
		static const inline std::string STRING = "text.string";
		static const inline std::string OFFSET_X = "text.offset.x";
		static const inline std::string OFFSET_Y = "text.offset.y";
		static const inline std::string CHARACTER_SIZE = "text.characterSize";
		static const inline std::string TEXT_ALIGNMENT = "text.align";
		static const inline std::string SHOW_WIREFRAME = "text.showWireframe";

		static const inline bool SHOW_WIREFRAME_DEFAULT = false;

	private:		
		struct Components {
			TextComponent& textComponent;
			PositionComponent& positionComponent;
			TIEntity& tientity;
		};
		std::list<Components> components;
};

}
#endif 
