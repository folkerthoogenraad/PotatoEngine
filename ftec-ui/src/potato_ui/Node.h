#pragma once

#include "Panel.h"

namespace potato {

	class NodeEditor;
	class Node;
	class NodeNotch;

	class NodeNotch : public Panel {
	public:
		NodeNotch();

		void drawSelf(ftec::Graphics2D &graphics) override;
		void onDrag(Event &event) override;
		Size getPreferredSize() override;
		
		bool inBounds(ftec::Vector2i point) const;
	};

	class Node : public Panel {
	protected:
		std::string m_Title;
		NodeEditor *m_NodeEditor;

		std::shared_ptr<Panel> m_Content;
		std::vector<std::shared_ptr<NodeNotch>> m_Inputs;
		std::vector<std::shared_ptr<NodeNotch>> m_Outputs;
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

		std::vector<std::shared_ptr<Panel>> getChildren() const override;
	};
}