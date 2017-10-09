#pragma once

#include <map>
#include "util/hash.h"
#include "math/Vector4.h"
#include "graphics/Sprite.h"

// Maybe be way more specific, but not important right now.
#define COLOR_TEXT_LIGHT		"ColorTextLight"
#define COLOR_TEXT_MEDIUM		"ColorTextMedium"
#define COLOR_TEXT_DARK			"ColorTextDark"

#define COLOR_PRIMARY_LIGHTEST	"ColorPrimaryLightest"
#define COLOR_PRIMARY_LIGHT		"ColorPrimaryLight"
#define COLOR_PRIMARY_MEDIUM	"ColorPrimaryMedium"
#define COLOR_PRIMARY_DARK		"ColorPrimaryDark"
#define COLOR_PRIMARY_DARKEST	"ColorPrimaryDarkest"

namespace potato {
	class PotatoStyle {
	private:
		std::map<ftec::HashType, ftec::Color32> m_Colors;
		std::map<ftec::HashType, ftec::Sprite> m_Sprites;

		ftec::Color32 m_DefaultColor = ftec::Color32(0xff, 0x14, 0x93, 0xff);
		ftec::Sprite m_DefaultSprite;
	public:

		void setColor(ftec::HashType hash, ftec::Color32 color);
		ftec::Color32 getColor(ftec::HashType hash) const;

		void setSprite(ftec::HashType hash, ftec::Sprite sprite);
		const ftec::Sprite &getSprite(ftec::HashType hash) const;

		void setDefaultSprite(ftec::Sprite sprite);
		void setDefaultColor(ftec::Color32 color);


	};
}