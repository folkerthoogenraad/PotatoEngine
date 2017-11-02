#pragma once

#include "potato_ui/Canvas.h"

namespace ftec {

	class TestCanvas : public potato::Canvas {
		bool m_Typed;
		bool m_Clicked;
		Vector2f m_Position;
	public:
		TestCanvas(std::shared_ptr<EngineContext> context);

		void onPreEvents() override;

		void drawSelf(Graphics2D &graphics, const potato::PotatoStyle &style) override;

		virtual void onClick(Event &evt) override;

		virtual void onHoverEnter(Event &evt) override;
		virtual void onHoverLeave(Event &evt) override;
		virtual void onHover(Event &evt) override;

		virtual void onDrag(Event &evt) override;
		virtual void onHoverOrDrag(Event &evt) override;

		virtual void onMousePressed(Event &evt) override;
		virtual void onMouseReleased(Event &evt) override;

		virtual void onKeyTyped(Event &evt) override;
		virtual void onKeyPressed(Event &evt) override;
		virtual void onKeyReleased(Event &evt) override;

	};
}