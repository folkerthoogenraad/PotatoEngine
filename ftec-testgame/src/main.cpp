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

	if (!saveImage(*image, "mario_res.png")) {
		LOG("Failed to load image");
	}
}

int main(void)
{
	using namespace ftec;

	//ftec::DesktopEngine::create<ftec::Razura>();
	
	test();

	WAIT();

	return 0;
}

