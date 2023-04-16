#ifndef SPRITECOMPONENTSYSTEM_H
#define SPRITECOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <string>

#include "objects/components/PositionComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class SpriteComponentSystem : public Singleton<SpriteComponentSystem>, public OwnsComponent<SpriteComponent> {
	public:
		SpriteComponentSystem();
		void update(const float);
		SpriteComponent& addComponent(TIEntity&);
		SpriteComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);

		void setComponentProperty(const std::string&, bool, TIEntity&);
		void setComponentProperty(const std::string&, float, TIEntity&);
		void setComponentProperty(const std::string&, const std::string&, TIEntity&);
		sol::object getComponentProperty(const std::string&, TIEntity&);

		void addWireframe(TIEntity&);

		static const inline std::string SPRITE = "sprite";
		static const inline std::string DRAWN = "sprite.drawn";
		static const inline std::string TEXTURE = "sprite.texture";
		static const inline std::string WIDTH = "sprite.width";
		static const inline std::string HEIGHT = "sprite.height";
		static const inline std::string ORIGIN_X = "sprite.origin.x";
		static const inline std::string ORIGIN_Y = "sprite.origin.y";
		static const inline std::string REPEATED = "sprite.repeated";
		static const inline std::string ROTATES = "sprite.rotates";
		static const inline std::string CONSTRAIN_PROPORTIONS = "sprite.constrainProportions";

		static const inline std::string MISSING_TEXTURE_NAME = "missing_texture.png";
	private: 
		struct Components {
			SpriteComponent& spriteComponent;
			PositionComponent& positionComponent;
		};
		std::list<Components> components;

        void setTextureFields(SpriteComponent&, const sf::Texture&);
        void setTextureFields(SpriteComponent&, float, float);
        void setTextureFields(SpriteComponent&, const sf::Texture&, float, float);
};

}
#endif 
