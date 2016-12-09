#pragma once

namespace potato {

	class LayoutParams {
	public:
		enum LayoutScaling {
			EXACT, WRAP_CONTENT, MATCH_PARENT
		};

		LayoutScaling m_WidthScaling = WRAP_CONTENT;
		LayoutScaling m_HeightScaling = WRAP_CONTENT;

		ftec::Vector2i m_Size = ftec::Vector2i(-1,-1);

		float m_Weight = 1.0;

	};
}