#include "Font.h"

#include <fstream>
#include <sstream>
#include <vector>

#include "logger/log.h"
#include "engine/Engine.h"
#include "graphics/Texture.h"

#include "GL.h"

#include "math/math.h"

//Freetype stuff <3
#include <ft2build.h>
#include FT_FREETYPE_H

namespace ftec {

	bool Font::hasCharacter(char input) const
	{
		return m_Characters.find(input) != m_Characters.end();
	}

	bool Font::getCharacter(char input, FontCharacter &out) const
	{
		auto i = m_Characters.find(input);
		
		if (i == m_Characters.end())
			return false;

		out = i->second;
		return true;
	}

	Vector2f Font::measure(const std::string &text)
	{
		Vector2f rect(0, m_Size); //TODO fix this height stuff

		float currentX = 0;

		for (char c : text) {
			if (c == '\n') {
				currentX = 0;
				rect.y += m_Size; //TODO fix this multiline stuff
				continue;
			}

			FontCharacter fc;
			if (getCharacter(c, fc)) {
				currentX += fc.xadvance;
				rect.x = std::fmax(rect.x, currentX);
			}
		}

		return rect;
	}

	//TODO make this cleaner
	struct Library {
		FT_Library ft;

		Library()
		{
			if (FT_Init_FreeType(&ft)) {
				LOG_ERROR("Could not initialize freetype library");
			}
		}
		~Library()
		{
			FT_Done_FreeType(ft);
		}
	};

	std::shared_ptr<Font> Font::load(const std::string & name)
	{
		static Library lib;

		FT_Face face;

		if (FT_New_Face(lib.ft, name.c_str(), 0, &face)) {
			LOG_ERROR("Couldn't not open font");
			return std::make_shared<Font>();
		}

		FT_Set_Pixel_Sizes(
			face,   /* handle to face object */
			0,      /* pixel_width           */
			16);   /* pixel_height          */


		FT_GlyphSlot g = face->glyph;
		unsigned int w = 0, h = 0;

		//For all our chars
		for (int i = 32; i < 128; i++) {
			if (FT_Load_Char(face, i, FT_LOAD_DEFAULT)) {
				LOG("Coudn't load char : " << (char) i);
				continue;
			}

			w += g->bitmap.width;
			h = ftec::max(h, g->bitmap.rows);
		}

		//TODO make this generated
		w = 1024;
		h = 16;

		std::shared_ptr<Font> font = std::make_shared<Font>();
		std::shared_ptr<Texture> texture = std::make_shared<Texture>();

		font->m_Size = 16;
		font->m_Name = "Loadedfont";

		texture->bind();

		//Set the alignment
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
		texture->m_Width = w;
		texture->m_Height = h;

		//TODO load the images onto the texture and set the chars 
		//https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Text_Rendering_02
		
		int x = 0;

		//For all our chars
		for (int i = 32; i < 128; i++) {
			//FT_Load_Char(face, i, FT_LOAD_RENDER);

			int glyph_index = FT_Get_Char_Index(face, i);
			FT_Load_Glyph(
				face,          /* handle to face object */
				glyph_index,   /* glyph index           */
				FT_LOAD_DEFAULT);  /* load flags, see below */
			FT_Render_Glyph(face->glyph,   /* glyph slot  */
				FT_RENDER_MODE_NORMAL); /* render mode */

			glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows,
				GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

			char c = (char)i;

			FontCharacter ch;
			Rectanglef rect( //TODO correct the rows here
				(float)x, 0.0, (float)g->bitmap.width, (float)g->bitmap.rows
			);

			ch.sprite = Sprite(texture, rect);
			ch.character = c;

			//TODO update font metrics

			ch.xadvance = g->advance.x >> 6;
			ch.yadvance = g->advance.y >> 6;
			ch.top = g->bitmap_top;
			ch.left = g->bitmap_left;
			ch.width = g->bitmap.width;
			ch.height = g->bitmap.rows;

			x += g->bitmap.width;

			//TODO this should not be a map probably
			font->m_Characters.insert(std::make_pair(c, ch));
		}
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

		texture->unbind();
		return font;
	}

#ifdef LEGACY
	std::shared_ptr<Font> Font::load(const std::string & name)
	{
		using namespace std;

		auto font = std::make_shared<Font>();

		std::vector<std::shared_ptr<Texture>> textures;

		fstream input(name);

		if (!input) {
			LOG_ERROR("Failed to load font : " << name);
			return font;
		}

		while (input) {
			string line;
			getline(input, line);

			stringstream reader(line);

			string type;
			reader >> type;

			auto parseValue = [&]() -> std::tuple<bool, std::string, std::string> {
				string f;

				reader >> f;

				int index = f.find('=');
				
				if (index < 0)
					return std::make_tuple(false, "", "");
				else
					return std::make_tuple(true, f.substr(0, index), f.substr(index + 1));
			};

			auto parseCharacter = [&](FontCharacter &c) -> bool{
				
				auto value = parseValue();

				if (!get<0>(value) || get<1>(value) != "id")
					return false;
				
				char ch = (char)stoi(get<2>(value));

				auto xv = parseValue();
				auto yv = parseValue();
				auto wv = parseValue();
				auto hv = parseValue();

				Rectanglef rect = Rectanglef(
					(float)stoi(get<2>(xv)),
					(float)stoi(get<2>(yv)),
					(float)stoi(get<2>(wv)),
					(float)stoi(get<2>(hv))
				);

				//xoffset //yoffset
				parseValue(); parseValue();
				
				auto xadv = parseValue();

				if (!get<0>(xadv) || get<1>(xadv) != "xadvance")
					return false;

				auto pagev = parseValue();

				if (!get<0>(pagev) || get<1>(pagev) != "page")
					return false;

				int pageIdx = stoi(get<2>(pagev));

				c.xadvance = stoi(get<2>(xadv));

				c.sprite = std::make_shared<Sprite>(
					textures[pageIdx],
					rect
					);

				c.character = ch;

				return true;
			};

			if (type == "info") {
				//LOG_DEBUG("Ignoring info");
				auto face = parseValue();
				if (!get<0>(face) || get<1>(face) != "face") {
					LOG_ERROR("NOT A FACE ):");
				}
				font->m_Name = get<2>(face).substr(1, get<2>(face).size() - 2);
				auto size = parseValue();
				if (!get<0>(size) || get<1>(size) != "size") {
					LOG_ERROR("NOT A SIZE ):");
				}
				font->m_Size = stoi(get<2>(size));
			}
			else if (type == "common") {
				//LOG_DEBUG("Ignoring common");
			}
			else if (type == "kerning") {
				//LOG_DEBUG("Kerning currently unsupported");
			}
			else if (type == "page") {
				//LOG_DEBUG("Partial support for paging currently. If pages are not in ID order, this code will break");
				parseValue();
				auto p = parseValue();
				if (!get<0>(p) || get<1>(p) != "file") {
					LOG_ERROR("Failed to parse page!");
				}
				else {
					string &s = get<2>(p);
					string result = s.substr(1, s.length() - 2);
					//Surrounded by quotes

					//Hardcoded relative pathing (TODO FIX THIS SOMEDAY MAN)
					textures.push_back(Engine::getResourceManager().load<Texture>("fonts/" + result));
				}
			}
			else if (type == "chars") {
				//Ignore this for now
			}
			else if (type == "char") {
				FontCharacter c;
				if (parseCharacter(c)) {
					font->m_Characters.insert(make_pair(c.character, c));
				}
				else {
					LOG_ERROR("Failed to parse character");
				}
			}
		}

		return font;
	}
#endif
}
