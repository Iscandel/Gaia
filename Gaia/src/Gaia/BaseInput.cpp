#include "Gaia/BaseInput.h"

namespace gaia
{
	std::queue<KeyboardEvent> BaseInput::myKeyboardEv;
	std::queue<MouseEvent> BaseInput::myMouseEv;
}