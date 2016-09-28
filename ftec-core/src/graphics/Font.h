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

	class Font : public ManagableResource {
	private:
		std::map<char, FontCharacter> m_Characters;
	public:
		bool hasCharacter(char input) const;
		const FontCharacter &getCharacter(char input) const;

		static std::shared_ptr<Font> load(const std::string &name);
	};
}