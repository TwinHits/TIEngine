#ifndef COLLIDESCOMPONENTSYSTEM_H
#define COLLIDESCOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <sol/sol.hpp>

#include "objects/components/CollidesComponent.h"
#include "objects/tientities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"

namespace TIE {

class CollidesComponentSystem : public Singleton<CollidesComponentSystem>, public OwnsComponent<CollidesComponent> {
	public:
		CollidesComponentSystem();
		void update(const float);
		CollidesComponent& addComponent(TIEntity&);
		CollidesComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);
		
		void setComponentProperty(const std::string&, bool, TIEntity&);
		sol::object getComponentProperty(const std::string&, TIEntity&);
			
		const static inline std::string COLLIDES = "collides";
		const static inline std::string IS_COLLIDABLE = "collides.collidable";
		const static inline std::string IS_COLLIDES = "collides.collides";

	private:        
		struct Components {
			CollidesComponent& collidesComponent;
			TIEntity& tientity;
		};
		std::list<Components> components;

		void checkHitboxCollisions(Components&, Components&);

		GlobalId hitboxCollisionMessageSubscription = 0;
		GlobalId traceCollisionMessageSubscription = 0;
};

}
#endif
