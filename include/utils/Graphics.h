#ifndef GRAPHICSHELPERS_H
#define GRAPHICSHELPERS_H

#include "objects/entities/TIEntity.h"

namespace TIE {
    namespace Graphics {
        void setDrawn(TIEntity&, const bool);
        const bool isDrawn(TIEntity&);
    }
}

#endif