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

	void Node::setNodeEditor(NodeEditor * editor)
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

		Panel::updateLayout();
	}

	void Node::onMousePressed(Event & event)
	{
		if (m_NodeEditor) {
			m_NodeEditor->setFocusNode(this);
			updateLayout();
		}
		event.consume();
	}

	void Node::setContent(std::shared_ptr<Panel> p) {
		m_Content = p;
		initChild(p);
		updateLayout();
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

		if (m_Content)
			p.push_back(m_Content);

		for (auto i : m_Inputs)
			p.push_back(i);

		for (auto i : m_Outputs)
			p.push_back(i);

		return p;
	}


	static const float RADIUS = 6;

	NodeNotch::NodeNotch()
	{
	}

	void NodeNotch::drawSelf(ftec::Graphics2D & graphics)
	{
		Bounds b = getGlobalBounds();

		graphics.setColor(ftec::Color32::dkgray());
		graphics.drawCircle(ftec::Circlef(
			b.center(),
			RADIUS
		), false);

		if (isPressed()) {
			graphics.drawLine(ftec::Line2f(
				b.center(),
				ftec::Input::getMousePosition()
			));
		}
	}

	void NodeNotch::onDrag(Event & event)
	{
		LOG("Je moeder <3");
	}
	Size NodeNotch::getPreferredSize()
	{
		return Size(RADIUS * 2, RADIUS * 2);
	}
	bool NodeNotch::inBounds(ftec::Vector2i point) const
	{
		return ftec::distance(getGlobalBounds().center(), point) < RADIUS;
	}
}
