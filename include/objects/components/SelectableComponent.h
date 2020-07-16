#ifndef SELECTABLECOMPONENT
#define SELECTABLECOMPONENT

#include "objects/components/Component.h"

namespace TIE {

class SelectableComponent : public Component {
	public: 
		SelectableComponent() {};
		~SelectableComponent() {};

		bool isSelectable();
		void setSelectable(bool);

		bool isSelected();
		void setSelected(bool);
	private:
		bool selectable = false;
		bool selected = false;
};

}

#endif
