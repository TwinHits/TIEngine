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
		
	private:
		void drawSelf(sf::RenderWindow&, sf::RenderStates) const;
		void updateSelf(const float);

		Layer layer;
};

}
#endif
