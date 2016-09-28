#include "Razura.h"
#include "scene/Scene.h"
#include "engine/Engine.h"
#include "engine/Input.h"
#include "NoClipCameraEntity.h"
#include "graphics/Graphics.h"

#include "graphics/GraphicsState.h"
#include "graphics/Shader.h"

#include "graphics/Graphics2D.h"
#include "math/math.h"
#include "graphics/Font.h"

namespace ftec {

	Razura::Razura()
		:sprite(Engine::getResourceManager().load<Texture>("textures/spritesheet.png"), rect2f(0, 0, 16, 16))
	{
		Engine::getResourceManager().load<Font>("fonts/default12.fnt");
	}


	float f = 0;
	float t = 0;
	bool running = false;

	void Razura::update()
	{
		if (Input::isKeyPressed(GLFW_KEY_SPACE)) {
			running = !running;
		}
		
		const float dist = 256.f;
		const float speed = 3.f;
		
		if (running) {

			t += Time::deltaTime * speed;
			if (t > 1) {
				t = 1;
				f = dist;
			}
		}
		else {
			t -= Time::deltaTime * speed;
			if (t < 0) {
				t = 0;
				f = 0;
			}
		}
		f = tween(0.f, dist, t, curves::CubicBezier());
	}

	void Razura::render()
	{
		Graphics2D graphics;

		graphics.drawClear();
		graphics.drawSprite(sprite, vec2f(64 + f, 64));

		graphics.drawString("Font rendering test `~1!2@3#4$5%6^7&8*9(0)-_=+\\][{};':\",./<>?", vec2f(2,128));
	}

	void Razura::init()
	{
		
	}

	void Razura::destroy()
	{

	}
}
