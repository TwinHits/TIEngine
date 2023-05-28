#ifndef TIENTITYFACTORY_H
#define TIENTITYFACTORY_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <sol/sol.hpp>

#include "objects/tientities/TIEntity.h" 
#include "objects/GlobalId.h"
#include "objects/ScriptTableReader.h"

namespace TIE {

class TIEntityFactory {
	public:
		TIEntityFactory();
		TIEntityFactory(const sol::table&);
		TIEntityFactory(const TIEntityFactory&) {};

		const GlobalId getId();

		const bool hasReader();
		const ScriptTableReader* getReader();
		const ScriptTableReader* getReader() const;

		TIEntityFactory& setName(std::string);
		const std::string& getName();

		void setShowWireFrame(const bool);
		const bool getShowWireframe();
		const bool getShowWireframe() const;

		TIEntityFactory& setParent(TIEntity*);

		TIEntity& build();

		static const inline std::string NAME = "tientity.name";
		static const inline std::string SHOW_WIREFRAME = "tientity.showWireframe";

		~TIEntityFactory() {};

	private:
		GlobalId id = 0;
		std::string name = "";
		bool showWireframe = false;
		TIEntity* parent = nullptr;
		std::unique_ptr<ScriptTableReader> reader;
};

}
#endif
