#ifndef TEXTCOMPONENTSYSTEM_H
#define TEXTCOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <string>

#include <SFML/Graphics.hpp>

#include "managers/ConfigManager.h"
#include "objects/components/TextComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class TextComponentSystem : public Singleton<TextComponentSystem>, public OwnsComponent<TextComponent> {
	public:
		TextComponentSystem();
		void update(const float);
		TextComponent& addComponent(TIEntity&);
		TextComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);

		void setComponentProperty(const std::string&, bool, TIEntity&);
		void setComponentProperty(const std::string&, float, TIEntity&);
		void setComponentProperty(const std::string&, const std::string&, TIEntity&);
		sol::object getComponentProperty(const std::string&, TIEntity&);

		std::pair<GlobalId, GlobalId> addWireframe(TIEntity& tientity);
		static void setOriginForTextAlignment(TextComponent&);

		static const inline std::string TEXT = "text";
		static const inline std::string DRAWN = "text_drawn";
		static const inline std::string STRING = "string";
		static const inline std::string FONT = "font";
		static const inline std::string OFFSET = "offset";
		static const inline std::string OFFSET_X = "offset_x";
		static const inline std::string OFFSET_Y = "offset_y";
		static const inline std::string CHARACTER_SIZE = "characterSize";
		static const inline std::string TEXT_ALIGNMENT = "align";

		static const inline std::string FONT_DEFAULT = ConfigManager::Instance()->getEngineFontName();

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
