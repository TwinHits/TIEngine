#ifndef SPRITECOMPONENTSYSTEM_H
#define SPRITECOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include "objects/components/PositionComponent.h"
#include "objects/components/SpriteComponent.h"

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

		std::pair<GlobalId, GlobalId> addWireframe(TIEntity&);

		static const inline std::string SPRITE = "sprite";
		static const inline std::string DRAWN = "sprite_drawn";
		static const inline std::string TEXTURE = "texture";
		static const inline std::string WIDTH = "sprite_width";
		static const inline std::string HEIGHT = "sprite_height";
		static const inline std::string ORIGIN = "origin";
		static const inline std::string ORIGIN_X = "origin_x";
		static const inline std::string ORIGIN_Y = "origin_y";
		static const inline std::string REPEATED = "repeated";
		static const inline std::string ROTATES = "sprite_rotates";
		static const inline std::string CONSTRAIN_PROPORTIONS = "constrainProportions";

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
