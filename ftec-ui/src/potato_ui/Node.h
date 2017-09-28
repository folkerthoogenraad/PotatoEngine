#pragma once

#include "Panel.h"

namespace potato {

	class NodeEditor;

	class Node : public Panel {
	protected:
		std::string m_Title;
		NodeEditor *m_NodeEditor;
	public:
		Node();
		Node(std::string title);

		void setTitle(std::string title);
		void setNodeEditor(NodeEditor* editor);
		void setContent(std::shared_ptr<Panel> p);
	public:
		void drawSelf(ftec::Graphics2D &graphics) override;
		void onDrag(Event &event) override;
		void updateLayout() override;
		void onMousePressed(Event &event) override;
		Size getPreferredSize() override;
	};
}