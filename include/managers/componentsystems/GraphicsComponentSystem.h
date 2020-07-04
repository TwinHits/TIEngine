#ifndef GRAPHICSCOMPONENTSYSTEM_H
#define GRAPHICSCOMPONENTSYSTEM_H

#include "ComponentSystem.h"

#include <SFML/Graphics.hpp>

#include "objects/components/SpriteComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/entities/TIEntity.h"

namespace TIE {

class GraphicsComponentSystem : public ComponentSystem {
	public:
		static void draw(TIEntity&, sf::RenderTarget&, sf::RenderStates);

		static SpriteComponent* addSpriteComponent(TIEntity&);
		static TextComponent* addTextComponent(TIEntity&);

		static void setDrawn(TIEntity&, bool);
		static bool isDrawn(TIEntity&);

	private: 
		GraphicsComponentSystem() {};
};

}
#endif 
