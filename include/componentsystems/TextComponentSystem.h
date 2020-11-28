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
		const std::string& getName();

		static const inline std::string DRAWN = "drawn.drawn";
		static const inline std::string TEXT = "drawn.text";
		static const inline std::string OFFSET_X = "drawn.offset.x";
		static const inline std::string OFFSET_Y = "drawn.offset.y";

	private:		
		struct Components {
			TextComponent& textComponent;
			PositionComponent& positionComponent;
		};
		std::vector<Components> components;
};

}
#endif 
