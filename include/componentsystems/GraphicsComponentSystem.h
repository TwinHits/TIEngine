#ifndef GRAPHICSCOMPONENTSYSTEM_H
#define GRAPHICSCOMPONENTSYSTEM_H

#include "ComponentSystem.h"

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/SpriteComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"

namespace TIE {

class GraphicsComponentSystem : public ComponentSystem {
	public:
		static void draw(TIEntity&, sf::RenderTarget&, sf::RenderStates);

		static SpriteComponent* addSpriteComponent(TIEntity&);
		static SpriteComponent* addSpriteComponent(const TIEntityFactory&, TIEntity&);
		static TextComponent* addTextComponent(TIEntity&);
		static TextComponent* addTextComponent(const TIEntityFactory&, TIEntity&);

		static void setDrawn(TIEntity&, bool);
		static bool isDrawn(TIEntity&);

		static const std::string DRAWN;
		static const std::string TEXTURE;
		static const std::string TEXT;
	private: 
		GraphicsComponentSystem() {};
};

}
#endif 
