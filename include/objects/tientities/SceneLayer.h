#ifndef SCENELAYER_H
#define SCENELAYER_H

#include "objects/tientities/TIEntity.h"

namespace TIE {

class SceneLayer : public TIEntity {
	public:
		SceneLayer() {};
		virtual ~SceneLayer() {};

		void setViewId(GlobalId);
		GlobalId getViewId();

		virtual bool isSceneLayer();
		
	private:
		GlobalId viewId = 0;
};

}
#endif
