#ifndef TIENTITYEXPLORER_H
#define TIENTITYEXPLORER_H

#include "objects/tientities/common/SceneLayer.h"

namespace TIE {

class TIEntityExplorer : public SceneLayer {
    public:
        TIEntityExplorer();
        ~TIEntityExplorer() {};

    private:
        void setBackgroundSize(const sf::Vector2i&);
        void setBackgroundPosition(const sf::Vector2i&);

        void onToggleShowHide();
        void onWindowSizeChange();

};

}

#endif
