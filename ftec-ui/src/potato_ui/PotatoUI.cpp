#include "PotatoUI.h"
#include "Panel.h"

namespace potato {
	//https://www.materialpalette.com/blue-grey/grey

	ftec::color32 PotatoColor::primaryText =	ftec::color32(0x21, 0x21, 0x21, 0xFF);
	ftec::color32 PotatoColor::secondaryText =	ftec::color32(0x75, 0x75, 0x75, 0xFF);

	ftec::color32 PotatoColor::darkPrimary =	ftec::color32(0x45, 0x5A, 0x64, 0xFF);
	ftec::color32 PotatoColor::primary =		ftec::color32(0x60, 0x7D, 0x8B, 0xFF);
	ftec::color32 PotatoColor::lightPrimary =	ftec::color32(0xCF, 0xD8, 0xDC, 0xFF);

	ftec::color32 PotatoColor::divider =		ftec::color32(0xBD, 0xBD, 0xBD, 0xFF);
	ftec::color32 PotatoColor::accent =			ftec::color32(0x9E, 0x9E, 0x9E, 0xFF);
	ftec::color32 PotatoColor::iconsText =		ftec::color32(0xFF, 0xFF, 0xFF, 0xFF);


	std::string PotatoClipboard::data = "";
	//TODO make this use the windows clipboard
	const std::string &PotatoClipboard::getData() {
		return data;
	}

	void PotatoClipboard::setData(const std::string &input) {
		data = input;
	}

	void PotatoUI::update()
	{
		if (root) {
			root->update();
		}
	}

	void PotatoUI::render()
	{
		graphics.resetClip();
		graphics.drawClear();
		graphics.begin();

		if (root) {
			root->draw(graphics);
		}

		graphics.end();
	}

	void PotatoUI::setRoot(std::shared_ptr<Panel> root)
	{
		this->root = root;
	}

}
