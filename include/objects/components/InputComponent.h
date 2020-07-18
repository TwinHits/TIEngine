#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "objects/components/Component.h"

#include <string>

namespace TIE {

class InputComponent : public Component {
	public: 
		InputComponent() {};
		~InputComponent() {};

		const std::string& getClick();
		void setClick(const std::string&);

	private:
		std::string click = "";

};

}

#endif
