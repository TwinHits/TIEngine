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

		static const inline std::string TEXT = "text";
		static const inline std::string DRAWN = "text.drawn";
		static const inline std::string CONTENT = "text.text";
		static const inline std::string OFFSET_X = "text.offset.x";
		static const inline std::string OFFSET_Y = "text.offset.y";

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
