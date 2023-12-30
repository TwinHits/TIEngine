#ifndef TRACEFACTORY_H
#define TRACEFACTORY_H

#include "objects/GlobalId.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class TraceFactory {
    public:
		TraceFactory(TIEntity*);
		TraceFactory(TIEntity&);
		TraceFactory(const TraceFactory&) {};

		const GlobalId getId();
	
		TraceFactory& setParent(TIEntity&);

		TraceFactory& setMagnitude(const float);
		TraceFactory& setDirection(const float);

		TIEntity& build();

		static const inline std::string TRACE = "Trace";

    private:
		GlobalId id = 0;

		TIEntity* parent = nullptr;
		float magnitude = 0;
		float direction = 0;

};

}


#endif
