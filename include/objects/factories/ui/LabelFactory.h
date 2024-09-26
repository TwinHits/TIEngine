#ifndef LABELFACTORY_H
#define LABELFACTORY_H 

#include "objects/factories/ui/UIElementFactory.h"

#include "sol/sol.hpp"

#include <string>

#include "objects/ScriptTableReader.h"
#include "objects/tientities/TIEntity.h"


namespace TIE {

class LabelFactory : public UIElementFactory {
    public:
        LabelFactory();
        LabelFactory(const sol::table&);
        LabelFactory(const ScriptTableReader&);
        ~LabelFactory() {};

        TIEntity& build();
    private:

};

}

#endif 
