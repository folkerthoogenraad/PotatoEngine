#include "NodeEditor.h"

#include "math/Vector4.h"

namespace potato {

	NodeEditor::NodeEditor()
	{
		m_ActiveFirst = -1;
		m_Insets = Insets(0, 0, 0, 0);
	}

	void NodeEditor::addNode(std::shared_ptr<Node> node)
	{
		node->setNodeEditor(this);
		initChild(node);
		m_Children.push_back(node);
	}

	ftec::Vector2f NodeEditor::getCameraPosition() const
	{
		return m_CameraPosition;
	}

	void NodeEditor::setFocusNode(Node * node)
	{
		int index = 0;
		for (auto i : m_Children) {
			if (i.get() == node) {
				m_ActiveFirst = index;
				break;
			}
			index++;
		}
	}

	void NodeEditor::drawSelf(ftec::Graphics2D & graphics)
	{
		Bounds b = this->getGlobalBounds();

		graphics.setColor(ftec::Color32::white());
		graphics.drawRectangle(b, true);

		graphics.setColor(ftec::Color32::gray());

		for (float x = fmod(m_CameraPosition.x, 64.0f); x < b.right(); x += 64) {
			graphics.drawLine(ftec::Line2f(
				ftec::Vector2f(x, b.top()),
				ftec::Vector2f(x, b.bottom())
			));
		}
		for (float y = fmod(m_CameraPosition.y, 64.0f); y < b.right(); y += 64) {
			graphics.drawLine(ftec::Line2f(
				ftec::Vector2f(b.left(), y),
				ftec::Vector2f(b.right(), y)
			));
		}
	}

	Size NodeEditor::getPreferredSize()
	{
		return Size(100,100);
	}

	void NodeEditor::onPostEvents()
	{
		Panel::onPostEvents();

		if (m_ActiveFirst >= 0) {
			for (int i = m_ActiveFirst; i > 0; i--) {
				std::swap(
					m_Children[i],
					m_Children[i - 1]
				);
			}
			m_ActiveFirst = -1;
		}
	}

	void NodeEditor::onDrag(Event & event)
	{
		//Redundant? I think so
		if (!isPressed())
			return;

		m_CameraPosition += event.getMouseDelta();

		for (auto child : m_Children) {
			child->localbounds().position += event.getMouseDelta();
		}

		updateLayout();
	}

	void NodeEditor::updateLayout()
	{
		for (auto child : m_Children) {
			child->localbounds().size = child->getPreferredSize();
		}
		Panel::updateLayout();
	}
}
