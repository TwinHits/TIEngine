#ifndef INPUTMAP_H
#define INPUTMAP_H

#include "../templates/Singleton.h"

namespace TIE
{
	class InputMap
	{
		public:
			virtual void process(unsigned int);	

			InputMap();
			virtual ~InputMap();
		private:
	};
} 

#endif
