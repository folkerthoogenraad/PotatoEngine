#include "ContextMenuPanel.h"

namespace potato {
	ContextMenuPanel::ContextMenuPanel(std::shared_ptr<Panel> child)
	{
		m_Children.push_back(child);
	}
	void ContextMenuPanel::onMousePressed(Event & event)
	{
		m_UI->setContextMenu(nullptr);
	}
	Size ContextMenuPanel::getPreferredSize()
	{
		return Size(100,100);
	}
}
