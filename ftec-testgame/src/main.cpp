#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"
#include "potato_ui/Event.h"

#include "graphics/ImageHelper.h"

void test()
{
	using namespace ftec;

	auto image = loadImage("textures/mario.png");

	if (!image) {
		LOG("WTF");
		return;
	}

	LOG(image->getWidth());
	LOG(image->getHeight());

	LOG("Saving image");

	if (!saveImage(*image, "res.png")) {
		LOG("Failed to load image");
	}
}

void test2()
{
	using namespace ftec;
	Image image(255,255);

	for (int y = 0; y < image.getWidth(); y++) {
		for (int x = 0; x < image.getHeight(); x++) {
			image.setColor(x, y, Color32((uint8_t)x, (uint8_t)y,1,1));
		}
	}

	saveImage(image, "res.png");
}

int main(void)
{
	using namespace ftec;

	//ftec::DesktopEngine::create<ftec::Razura>();
	
	test();
	//test2();

	WAIT();

	return 0;
}

