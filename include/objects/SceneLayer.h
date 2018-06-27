#ifndef SCENELAYER_H
#define SCENELAYER_H

#include "objects/SceneNode.h"

namespace TIE {

class SceneLayer : public SceneNode {
	public:
		enum Layer {
			ROOT,
			ENGINE,
			CLIENT
		};

		SceneLayer();
		virtual ~SceneLayer();

		Layer getLayer();
		void setLayer(Layer);

		void setViewId(GlobalId);
		GlobalId getViewId();
		
	private:
		void drawSelf(sf::RenderTarget&, sf::RenderStates) const;
		void updateSelf(const float);

		Layer layer;
		GlobalId viewId;
};

}
#endif
