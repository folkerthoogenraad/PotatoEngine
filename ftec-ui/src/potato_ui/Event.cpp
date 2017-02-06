#include "Event.h"
#include "engine/Input.h"
#include "PotatoUI.h"

namespace potato {

	Event::Event(std::shared_ptr<PotatoUI> ui) : m_Consumed(false), m_UI(ui)
	{

	}
}