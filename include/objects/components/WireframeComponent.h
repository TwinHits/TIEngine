#ifndef WIREFRAMECOMPONENT_H
#define WIREFRAMECOMPONENT_H

#include "objects/components/Component.h"

#include <map>

#include <SFML/Graphics.hpp>

#include "objects/GlobalId.h"

namespace TIE {

class WireframeComponent : public Component {
	public:
		WireframeComponent() {};
		virtual ~WireframeComponent() {};

		void setShowWireframe(const bool);
		const bool getShowWireframe();

		void addWireframeShapeIds(const Component*, std::pair<GlobalId, GlobalId>);
		const std::pair<GlobalId, GlobalId>* getWireframeShapeIds(const Component*);

	private:
		bool showWireframe = false;
		
		// ptr: {origin, shape}
		std::map<const Component*, std::pair<GlobalId, GlobalId> > componentToWireframeShapeIds;
};

}
#endif
