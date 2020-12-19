#ifndef CACHECOMPONENT_H
#define CACHECOMPONENT_H

#include "objects/components/Component.h"

#include <sol/sol.hpp>

namespace TIE {

class CacheComponent : public Component {
    public:
        void setCache(sol::table&);
        sol::table& getCache();

    private:
        sol::table cache = sol::table();
};

}
#endif
