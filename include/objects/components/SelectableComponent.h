#ifndef SELECTABLECOMPONENT_H
#define SELECTABLECOMPONENT_H

#include "objects/components/Component.h"

namespace TIE {

	class SelectableComponent : public Component {
	public:
		SelectableComponent() {};
		virtual ~SelectableComponent() {};

		void setSelectable(const bool);
		const bool isSelectable();
		const bool isSelectable() const;

		void setSelected(const bool);
		const bool isSelected();
		const bool isSelected() const;

	private:
		bool selectable = false;
		bool selected = false;
	};

}
#endif
