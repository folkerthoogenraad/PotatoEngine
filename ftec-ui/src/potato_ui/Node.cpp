#include "Node.h"
#include "NodeEditor.h"
#include "graphics/Font.h"

#include "engine/Input.h"

#include "math/math.h"
#include "math/collision.h"

#include "logger/log.h"

namespace potato {

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

	void Node::drawSelf(ftec::Graphics2D & graphics)
	{
		Bounds bounds = getGlobalBounds();
		Bounds title = bounds;
		title.height() = 24;

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

			bounds.position.x = 0;
			bounds.position.y = 32;
			bounds.height() -= 32;

			m_Content->localbounds() = bounds;
		}


		Bounds bounds = localbounds();

		size_t s = 0;
		for (auto in : m_Inputs){
			Bounds b = Bounds::centered(0, 32 * s + 32, 16, 16);

			in->localbounds() = b;

			s++;
		}


		s = 0;
		for (auto in : m_Outputs) {
			Bounds b = Bounds::centered(bounds.width(), 32 * s + 32, 16, 16);

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
				m->setNode(this);
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
				m->setNode(this);
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

	void NodeNotch::drawSelf(ftec::Graphics2D & graphics)
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


		if (m_Type == NodeNotchType::Input) {
			auto ptr = m_ConnectedTo.lock();
			if (ptr) {
				graphics.drawLine(ftec::Line2f(
					b.center(),
					ptr->getGlobalBounds().center()
				));
			}
		}

		if (isPressed()) {
			graphics.drawLine(ftec::Line2f(
				b.center(),
				ftec::Input::getMousePosition()
			));
		}
	}

	void NodeNotch::onMouseReleased(Event & event)
	{
		if (!m_Node)
			return;

		std::shared_ptr<NodeEditor> editor = m_Node->getNodeEditor().lock();

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
			if (notch->m_Type != m_Type && notch->m_Node != m_Node) {
				m_ConnectedTo = notch;

				notch->m_ConnectedTo = get_as<NodeNotch>();
			}
		}
	}

	Size NodeNotch::getPreferredSize()
	{
		return Size(RADIUS * 2, RADIUS * 2);
	}

	void NodeNotch::setNode(Node * node)
	{
		m_Node = node;
	}

	bool NodeNotch::inBounds(ftec::Vector2i point) const
	{
		return ftec::distance(getGlobalBounds().center(), point) < RADIUS;
	}
}
