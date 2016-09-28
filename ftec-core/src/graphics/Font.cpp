#include "Font.h"

#include <fstream>
#include <sstream>
#include <vector>

#include "logger/log.h"
#include "engine/Engine.h"

namespace ftec {

	bool Font::hasCharacter(char input) const
	{
		return m_Characters.find(input) != m_Characters.end();
	}

	const FontCharacter & Font::getCharacter(char input) const
	{
		return m_Characters.find(input)->second;
	}

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

				rect2f rect = rect2f(
					(float)stoi(get<2>(xv)),
					(float)stoi(get<2>(yv)),
					(float)stoi(get<2>(wv)),
					(float)stoi(get<2>(hv))
				);

				//offset
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
					LOG("Loading texture " << result);

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
}
