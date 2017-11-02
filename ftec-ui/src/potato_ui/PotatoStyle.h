#pragma once

#include <map>
#include "util/hash.h"
#include "math/Vector4.h"
#include "graphics/Sprite.h"

namespace potato {
	class PotatoStyle {
	private:
		std::map<ftec::HashType, ftec::Color32> m_Colors;
		std::map<ftec::HashType, ftec::Sprite> m_Sprites;

		ftec::Color32 m_DefaultColor = ftec::Color32(0xff, 0x14, 0x93, 0xff);
		ftec::Sprite m_DefaultSprite;
	public:
		ftec::Color32 m_BackgroundColor = ftec::Color32(75, 75, 75, 0xff);
		ftec::Color32 m_DarkBackground = ftec::Color32(50, 50, 50, 0xff);
		ftec::Color32 m_LightBackground = ftec::Color32(215, 213, 179, 0xff);

		ftec::Color32 m_PrimaryColor = ftec::Color32(200, 200, 200, 0xff);
		ftec::Color32 m_SecondaryColor = ftec::Color32(100, 100, 100, 0xff);

		ftec::Color32 m_AccentColor = ftec::Color32(169, 206, 232, 0xff);
	public:

		void setColor(ftec::HashType hash, ftec::Color32 color);
		ftec::Color32 getColor(ftec::HashType hash) const;

		void setSprite(ftec::HashType hash, ftec::Sprite sprite);
		const ftec::Sprite &getSprite(ftec::HashType hash) const;

		void setDefaultSprite(ftec::Sprite sprite);
		void setDefaultColor(ftec::Color32 color);


	};
}