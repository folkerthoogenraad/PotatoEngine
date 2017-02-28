#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"
#include "potato_ui/Event.h"

#include "graphics/ImageHelper.h"

void test()
{
	using namespace ftec;

	Image image(255, 255);

	for (int y = 0; y < image.getWidth(); y++) {
		for (int x = 0; x < image.getWidth(); x++) {
			image.setColor(x, y, Color32::blue());
		}
	}

	if (!saveImage(image, "res.png")) {
		LOG("Failed to save image");
		return;
	}

	auto img = loadImage("res.png");

	if (!img) {
		LOG("Can't load image");
		return;
	}

	LOG((int)img->getColor(0, 0).r << ", " << (int)img->getColor(0, 0).g << ", " << (int) img->getColor(0, 0).b << ", " << (int)img->getColor(0, 0).a);
}

int main(void)
{
	using namespace ftec;

	//ftec::DesktopEngine::create<ftec::Razura>();
	
	test();

	WAIT();

	return 0;
}

