#pragma once

#include "potato_ui/Canvas.h"

namespace ftec {

	class TestCanvas : public potato::Canvas {
		bool m_Typed;
		bool m_Clicked;
		Vector2f m_Position;
	public:
		TestCanvas();

		void onPreEvents() override;

		void drawSelf(Graphics2D &graphics, const potato::PotatoStyle &style) override;

		virtual void onClick(potato::Event &evt) override;

		virtual void onHoverEnter(potato::Event &evt) override;
		virtual void onHoverLeave(potato::Event &evt) override;
		virtual void onHover(potato::Event &evt) override;

		virtual void onDrag(potato::Event &evt) override;
		virtual void onHoverOrDrag(potato::Event &evt) override;

		virtual void onMousePressed(potato::Event &evt) override;
		virtual void onMouseReleased(potato::Event &evt) override;

		virtual void onKeyTyped(potato::Event &evt) override;
		virtual void onKeyPressed(potato::Event &evt) override;
		virtual void onKeyReleased(potato::Event &evt) override;

	};
}