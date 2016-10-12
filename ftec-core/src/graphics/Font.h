#pragma once

#include <map>
#include "resources/ResourceManager.h"
#include "Sprite.h"

namespace ftec {

	struct FontCharacter {
	public:
		char character;
		int xadvance = 0;
		std::shared_ptr<Sprite> sprite = nullptr;
	};

	enum class FontAlign {
		CENTER = 0,
		LEFT = 1,
		RIGHT = 2,
		TOP = 1,
		BOTTOM = 2
	};

	class Font : public ManagableResource {
	private:
		std::map<char, FontCharacter> m_Characters;
		std::string m_Name;
		float m_Size;
	public:
		bool hasCharacter(char input) const;
		bool getCharacter(char input, FontCharacter &out) const; //TODO must be changed when there is a std::optional
		const std::string &getName() const { return m_Name; };
		float getSize() const { return m_Size; }

		vec2f measure(const std::string&);

		static std::shared_ptr<Font> load(const std::string &name);
	};
}