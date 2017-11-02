#pragma once

#include "Panel.h"

namespace potato {

	class ContextMenuPanel : public Panel {
	public:
		ContextMenuPanel(std::shared_ptr<ftec::EngineContext> context, std::shared_ptr<Panel> child);
		void onMousePressed(ftec::Event &event) override;

		Size getPreferredSize() override;
	};

}