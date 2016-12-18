#pragma once

#include <map>								//For std::map
#include <memory>							//For std::shared_ptr

#include "resources/ManageableResource.h"	//For ManageableResource
#include "Sprite.h"							//For FontCharacter::sprite

namespace ftec {

	struct FontCharacter {
	public:
		char character;

		int xadvance = 0;
		int yadvance = 0;
		int left = 0;
		int top = 0;

		int width;
		int height;

		Sprite sprite;
	};

	enum class FontAlign {
		CENTER = 0,
		LEFT = 1,
		RIGHT = 2,
		TOP = 1,
		BOTTOM = 2
	};

	class Font : public ManageableResource {
	private:
		std::map<char, FontCharacter> m_Characters;
		std::string m_Name;
		float m_Size;
	public:
		bool hasCharacter(char input) const;
		bool getCharacter(char input, FontCharacter &out) const;
		const std::string &getName() const { return m_Name; };
		float getSize() const { return m_Size; }

		Vector2f measure(const std::string&);

		static std::shared_ptr<Font> load(const std::string &name);

	private:
		
	};
}