#include "Node.h"
#include "NodeEditor.h"
#include "graphics/Font.h"

#include "engine/Input.h"

#include "math/math.h"
#include "math/collision.h"

#include "logger/log.h"

namespace potato {

	const float BAR_HEIGHT = 24;

	Node::Node()
	{
		this->m_Insets = Insets::none();
	}

	Node::Node(std::string title)
	{
		setTitle(title);
		this->m_Insets = Insets::none();
	}

	void Node::setTitle(std::string title)
	{
		this->m_Title = std::move(title);
	}

	void Node::setNodeEditor(std::weak_ptr<NodeEditor> editor)
	{
		m_NodeEditor = editor;
	}

	void Node::drawSelf(ftec::Graphics2D & graphics, const PotatoStyle& style)
	{
		Bounds bounds = getGlobalBounds();
		Bounds title = bounds;
		title.height() = BAR_HEIGHT;

		auto c = ftec::Color32::white();
		c.a = (uint8_t) 200;

		auto c2 = ftec::Color32::gray();
		c2.a = (uint8_t)200;

		graphics.setColor(c);
		graphics.drawRectangle(bounds, true);

		graphics.setColor(c2);
		graphics.drawRectangle(bounds, false);
		graphics.drawRectangle(title, true);

		graphics.setColor(ftec::Color32::white());
		graphics.setHorizontalAlign(ftec::FontAlign::CENTER);
		graphics.setVerticalAlign(ftec::FontAlign::CENTER);
		graphics.drawString(m_Title, title.center());
	}

	void Node::onDrag(Event & event)
	{
		if (!isPressed())
			return;

		localbounds().position += event.getMouseDelta();
		
		updateLayout();

		event.consume();
	}

	void Node::updateLayout() 
	{
		if(m_Content){
			Bounds bounds = localbounds();
			Size contentPreferedSize = m_Content->getPreferredSize();

			bounds.position.x = 8;
			bounds.size.width -= 16;

			bounds.position.y = BAR_HEIGHT;
			bounds.height() -= BAR_HEIGHT;

			// Exact, there is nothing we can do
			if (m_Content->layoutparams().m_WidthScaling == LayoutParams::EXACT)
				bounds.width() = layoutparams().m_Size.x;
			if (m_Content->layoutparams().m_HeightScaling == LayoutParams::EXACT)
				bounds.height() = layoutparams().m_Size.y;

			// Wrap content, we can do that
			if (m_Content->layoutparams().m_WidthScaling == LayoutParams::WRAP_CONTENT)
				bounds.width() = contentPreferedSize.width;
			if (m_Content->layoutparams().m_HeightScaling == LayoutParams::WRAP_CONTENT)
				bounds.height() = contentPreferedSize.height;

			// We don't have to do anything for MATCH_PARENT

			m_Content->localbounds() = bounds;
		}


		Bounds bounds = localbounds();

		size_t s = 0;
		for (auto in : m_Inputs){
			Bounds b = Bounds::centered(0, 32 * s + BAR_HEIGHT + 16, 16, 16);

			in->localbounds() = b;

			s++;
		}


		s = 0;
		for (auto in : m_Outputs) {
			Bounds b = Bounds::centered(bounds.width(), 32 * s + BAR_HEIGHT + 16, 16, 16);

			in->localbounds() = b;

			s++;
		}

		Panel::updateLayout();
	}

	void Node::onMousePressed(Event & event)
	{
		if (auto l = m_NodeEditor.lock()) {
			l->setFocusNode(this);
			updateLayout();
		}
		event.consume();
	}

	void Node::setContent(std::shared_ptr<Panel> p) {
		m_Content = p;
		initChild(p);
		updateLayout();
	}

	void Node::setInputs(int count)
	{
		if (m_Inputs.size() != count) {
			m_Inputs.clear();
			for (int i = 0; i < count; i++) {
				auto m = std::make_shared<NodeNotch>(NodeNotchType::Input);
				initChild(m);
				m->setNode(get_as<Node>());
				m_Inputs.push_back(m);
			}
		}
	}

	void Node::setOutputs(int count)
	{
		if (m_Outputs.size() != count) {
			m_Outputs.clear();
			for (int i = 0; i < count; i++) {
				auto m = std::make_shared<NodeNotch>(NodeNotchType::Output);
				initChild(m);
				std::dynamic_pointer_cast<Node>(shared_from_this());

				m->setNode(get_as<Node>());
				m_Outputs.push_back(m);
			}
		}
	}

	Size Node::getPreferredSize()
	{
		Size s = Size(128, 200);

		if (m_Content) {
			Size n = m_Content->getPreferredSize();

			s.x = ftec::max(s.x, n.x);
			s.y = ftec::max(s.y, n.y);
		}

		return s;
	}

	std::vector<std::shared_ptr<Panel>> Node::getChildren() const
	{
		std::vector<std::shared_ptr<Panel>> p;

		for (auto i : m_Inputs)
			p.push_back(i);

		for (auto i : m_Outputs)
			p.push_back(i);

		if (m_Content)
			p.push_back(m_Content);

		return p;
	}


	static const float RADIUS = 6;


	NodeNotch::NodeNotch(NodeNotchType type)
		: m_Type(type)
	{ }

	void NodeNotch::drawSelf(ftec::Graphics2D & graphics, const PotatoStyle& style)
	{
		Bounds b = getGlobalBounds();


		graphics.setColor(ftec::Color32::ltgray());
		graphics.drawCircle(ftec::Circlef(
			b.center(),
			RADIUS
		), true);

		graphics.setColor(ftec::Color32::dkgray());
		graphics.drawCircle(ftec::Circlef(
			b.center(),
			RADIUS
		), false);

		graphics.setLineWidth(2);
		if (m_Type == NodeNotchType::Input) {
			auto ptr = m_ConnectedTo.lock();
			if (ptr) {
				graphics.drawAutoBezier(
					b.center(),
					ptr->getGlobalBounds().center()
				);
			}
		}

		if (isPressed()) {
			graphics.drawAutoBezier(
				b.center(),
				ftec::Input::getMousePosition()
			);
		}

		graphics.setLineWidth(1);
	}

	void NodeNotch::onMouseReleased(Event & event)
	{
		auto node = m_Node.lock();

		if (!node)
			return;

		std::shared_ptr<NodeEditor> editor = node->getNodeEditor().lock();

		if (!editor)
			return;

		//Reset the old thing
		auto old = m_ConnectedTo.lock();

		if (old)
			old->m_ConnectedTo.reset();

		m_ConnectedTo.reset();


		//Add the new thing
		auto panel = editor->findPanelByPosition(event.getMousePosition());

		if (auto notch = std::dynamic_pointer_cast<NodeNotch>(panel)) 
		{
			//Input -> Output or other way around
			if (notch->m_Type != m_Type && notch->m_Node.lock() != node) {
				m_ConnectedTo = notch;

				notch->m_ConnectedTo = get_as<NodeNotch>();
			}
		}
	}

	Size NodeNotch::getPreferredSize()
	{
		return Size(RADIUS * 2, RADIUS * 2);
	}

	void NodeNotch::setNode(std::weak_ptr<Node> node)
	{
		m_Node = node;
	}

	bool NodeNotch::inBounds(ftec::Vector2i point) const
	{
		return ftec::distance(getGlobalBounds().center(), point) < RADIUS;
	}
}
