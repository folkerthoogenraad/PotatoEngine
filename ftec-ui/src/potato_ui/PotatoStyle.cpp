#include "PotatoStyle.h"

namespace potato {
	void PotatoStyle::setColor(ftec::HashType hash, ftec::Color32 color)
	{
		m_Colors[hash] = std::move(color);
	}

	ftec::Color32 PotatoStyle::getColor(ftec::HashType hash) const
	{
		auto c = m_Colors.find(hash);

		if (c == m_Colors.end())
			return m_DefaultColor;

		return c->second;
	}

	void PotatoStyle::setSprite(ftec::HashType hash, ftec::Sprite sprite)
	{
		m_Sprites[hash] = std::move(sprite);
	}

	const ftec::Sprite &PotatoStyle::getSprite(ftec::HashType hash) const
	{
		auto c = m_Sprites.find(hash);
		if (c == m_Sprites.end())
			return m_DefaultSprite;

		return c->second;
	}
	void PotatoStyle::setDefaultSprite(ftec::Sprite sprite)
	{
		m_DefaultSprite = std::move(sprite);
	}
	void PotatoStyle::setDefaultColor(ftec::Color32 color)
	{
		m_DefaultColor = color;
	}
}
