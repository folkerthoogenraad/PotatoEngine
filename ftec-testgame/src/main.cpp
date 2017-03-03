#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"
#include "potato_ui/Event.h"

#include "graphics/ImageHelper.h"

#include "util/not_null.h"
#include "graphics/SoftwareGraphics.h"

void test()
{
	using namespace ftec;

	Image image(255, 255);

	for (int y = 0; y < image.getWidth(); y++) {
		for (int x = 0; x < image.getWidth(); x++) {
			image.setColor(x, y, Color32::white());
		}
	}

	SoftwareGraphics graphics(&image);
	Paint paint;
	paint.color = Color::black();

	graphics.drawLine(paint, Vector2i(4, 4), Vector2i(16, 8));

	if (!saveImage(image, "res.png")) {
		LOG("Failed to save image");
		return;
	}
}

int main(void)
{
	using namespace ftec;

	ftec::DesktopEngine::create<ftec::Razura>();
	
	//test();

	WAIT();

	return 0;
}

