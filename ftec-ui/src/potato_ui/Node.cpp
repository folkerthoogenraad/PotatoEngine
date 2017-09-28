#include "Node.h"
#include "NodeEditor.h"
#include "graphics/Font.h"

#include "math/math.h"

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

		graphics.setColor(ftec::Color32::ltgray());
		graphics.drawRectangle(bounds, true);

		graphics.setColor(ftec::Color32::gray());
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
		if (m_Children.size() == 0)
			return;

		for (auto child : m_Children) {
			Bounds bounds = localbounds();

			bounds.position.x = 0;
			bounds.position.y = 32;
			bounds.height() -= 32;

			child->localbounds() = bounds;
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
		if (m_Children.size() == 0)
			m_Children.push_back(p);

		m_Children[0] = p;
		initChild(p);
	}

	Size Node::getPreferredSize()
	{
		Size s = Size(128, 200);

		if (m_Children.size() != 0) {
			Size n = m_Children.front()->getPreferredSize();

			s.x = ftec::max(s.x, n.x);
			s.y = ftec::max(s.y, n.y);
		}

		return s;
	}
}
