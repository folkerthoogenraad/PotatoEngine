#include "ContextMenuPanel.h"

namespace potato {
	ContextMenuPanel::ContextMenuPanel(std::shared_ptr<ftec::EngineContext> context, std::shared_ptr<Panel> child)
		: Panel(context)
	{
		m_Children.push_back(child);
	}
	void ContextMenuPanel::onMousePressed(ftec::Event & event)
	{
		m_UI->setContextMenu(nullptr);
	}
	Size ContextMenuPanel::getPreferredSize()
	{
		return Size(100,100);
	}
}
