#ifndef SPRITECOMPONENTSYSTEM_H
#define SPRITECOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <string>

#include "objects/components/PositionComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class SpriteComponentSystem : public Singleton<SpriteComponentSystem>, public ComponentSystem {
	public:
		SpriteComponentSystem();
		void update(const float);
		bool hasComponent(const TIEntity&);
		SpriteComponent& addComponent(TIEntity&);
		SpriteComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);
		const std::string& getName();

		bool setComponentProperty(const std::string&, bool, TIEntity&);
		bool setComponentProperty(const std::string&, float, TIEntity&);
		bool setComponentProperty(const std::string&, const std::string&, TIEntity&);
		sol::object getComponentProperty(const std::string&, TIEntity&);

		static const inline std::string SPRITE = "sprite";
		static const inline std::string DRAWN = "sprite.drawn";
		static const inline std::string TEXTURE = "sprite.texture";
		static const inline std::string WIDTH = "sprite.width";
		static const inline std::string HEIGHT = "sprite.height";
		static const inline std::string ORIGIN_X = "sprite.origin.x";
		static const inline std::string ORIGIN_Y = "sprite.origin.y";
		static const inline std::string REPEATED = "sprite.repeated";
		static const inline std::string ROTATES = "sprite.rotates";
		static const inline std::string SHOW_WIREFRAME = "sprite.showWireframe";
		static const inline std::string CONSTRAIN_PROPORTIONS = "sprite.constrainProportions";

		static const inline std::string MISSING_TEXTURE_NAME = "missing_texture.png";
		static const inline bool SHOW_WIREFRAME_DEFAULT = false;
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
