#ifndef PATHSCOMPONENTSYSTEM_H
#define PATHSCOMPONENTSYSTEM_H

#include "componentSystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include "objects/components/PathsComponent.h"

namespace TIE {

class PathsComponentSystem : public Singleton<PathsComponentSystem>, public OwnsComponent<PathsComponent> {
	public:
		PathsComponentSystem();
		void update(const float);
		PathsComponent& addComponent(TIEntity&);
		PathsComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);
		
		static const inline std::string PATHS = "paths";
	private:
		struct Components {
			PathsComponent& pathsComponent;
			TIEntity& tientity;
		};
		std::list<Components> components;
};

}
#endif
