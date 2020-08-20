#ifndef TEXTCOMPONENTSYSTEM_H
#define TEXTCOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/TextComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"

namespace TIE {

class TextComponentSystem : public Singleton<TextComponentSystem>, ComponentSystem {
	public:
		TextComponentSystem() {};
		void update(const float);
		TextComponent& addComponent(TIEntity&);
		void addComponent(const TIEntityFactory&, TIEntity&);

		static const std::string DRAWN;
		static const std::string TEXT;
		static const std::string DRAWN_KEY;
		static const std::string TEXT_KEY;
	private: 
};

}
#endif 
