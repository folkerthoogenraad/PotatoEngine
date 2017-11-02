#pragma once

#include "Panel.h"

namespace potato {

	class NodeEditor;
	class Node;
	class NodeNotch;

	enum class NodeNotchType {
		Input, Output
	};

	class NodeNotch : public Panel {
		NodeNotchType m_Type;
		std::weak_ptr<Node> m_Node; // TODO change all raw pointers?

		std::weak_ptr<NodeNotch> m_ConnectedTo;
	public:
		NodeNotch(std::shared_ptr<ftec::EngineContext> context, NodeNotchType type);

		void drawSelf(ftec::Graphics2D &graphics, const PotatoStyle &style) override;
		void onMouseReleased(ftec::Event &event) override;
		Size getPreferredSize() override;
		
		void setNode(std::weak_ptr<Node> node);

		bool inBounds(ftec::Vector2i point) const;
	};

	class Node : public Panel {
	protected:
		std::string m_Title;
		std::weak_ptr<NodeEditor> m_NodeEditor;

		std::shared_ptr<Panel> m_Content;
		std::vector<std::shared_ptr<NodeNotch>> m_Inputs;
		std::vector<std::shared_ptr<NodeNotch>> m_Outputs;
	public:
		Node(std::shared_ptr<ftec::EngineContext> context);
		Node(std::shared_ptr<ftec::EngineContext> context, std::string title);

		void setTitle(std::string title);
		void setNodeEditor(std::weak_ptr<NodeEditor> editor);
		std::weak_ptr<NodeEditor> getNodeEditor() const { return m_NodeEditor; };
		void setContent(std::shared_ptr<Panel> p);

		void setInputs(int count);
		void setOutputs(int count);
	public:
		void drawSelf(ftec::Graphics2D &graphics, const PotatoStyle& style) override;
		void onDrag(ftec::Event &event) override;
		void updateLayout() override;
		void onMousePressed(ftec::Event &event) override;
		Size getPreferredSize() override;

		std::vector<std::shared_ptr<Panel>> getChildren() const override;
	};
}