#ifndef SCENELAYERFACTORY_H
#define SCENELAYERFACTORY_H

#include <string>

#include "objects/SceneLayer.h"

namespace TIE {

class SceneLayerFactory {
    public:
        SceneLayerFactory();

        SceneLayer& build();

        SceneLayerFactory& setName(const std::string&);
        SceneLayerFactory& setParent(TIEntity&);
        SceneLayerFactory& setViewId(GlobalId);
        SceneLayerFactory& setLayer(SceneLayer::Layer);

    private:
        std::string name = "";
        TIEntity* parent = nullptr;
        GlobalId viewId = 0;
        SceneLayer::Layer layer = SceneLayer::Layer::CLIENT;
};

}


#endif SCENELAYERFACTORY_H

