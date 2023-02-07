#ifndef SCENELAYER_H
#define SCENELAYER_H

#include "objects/tientities/TIEntity.h"

namespace TIE {

class SceneLayer : public TIEntity {
	public:
		enum class Layer {
			ROOT,
			ENGINE,
			CLIENT,
			WORLD,
		};

		SceneLayer() {};
		virtual ~SceneLayer() {};

		Layer getLayer();
		void setLayer(Layer);

		void setViewId(GlobalId);
		GlobalId getViewId();

		virtual bool isSceneLayer();
		
	private:
		Layer layer = Layer::ROOT;
		GlobalId viewId = 0;
};

}
#endif
