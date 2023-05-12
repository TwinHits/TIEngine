#ifndef SCENELAYERFACTORY_H
#define SCENELAYERFACTORY_H

#include <string>

#include "objects/tientities/SceneLayer.h"

namespace TIE {

class SceneLayerFactory {
    public:
        SceneLayerFactory();

        SceneLayer& build();

        SceneLayerFactory& setName(const std::string&);
        SceneLayerFactory& setParent(TIEntity&);
        SceneLayerFactory& setViewId(GlobalId);

    private:
        std::string name = "";
        TIEntity* parent = nullptr;
        GlobalId viewId = 0;
};

}


#endif SCENELAYERFACTORY_H

