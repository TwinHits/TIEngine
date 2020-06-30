#ifndef SCENENODE_H
#define SCENENODE_H

#include "objects/entities/TIEntity.h"

namespace TIE {
class SceneNode { 
	public:
		SceneNode();
		SceneNode(const SceneNode&) {};
		virtual ~SceneNode() {};

};

}
#endif

