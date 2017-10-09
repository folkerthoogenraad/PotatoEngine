#pragma once

#include "Panel.h"

#include "Node.h"

#include "math/Vector2.h"

namespace potato {
	class NodeEditor : public Panel {
	protected:
		ftec::Vector2f m_CameraPosition;
		int m_ActiveFirst;
	public:
		NodeEditor();

		void addNode(std::shared_ptr<Node> node);
		ftec::Vector2f getCameraPosition() const;
		void setFocusNode(Node* node);
	public:
		void drawSelf(ftec::Graphics2D &graphics, const PotatoStyle &style) override;
		Size getPreferredSize() override;
		void onPostEvents() override;
		void onDrag(Event &event) override;
		void updateLayout() override;

	};
}