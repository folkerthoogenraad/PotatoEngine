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
		:sprite(Engine::getResourceManager().load<Texture>("textures/spritesheet.png"), rect2f(16, 0, 33, 33))
	{

	}

	float z = 0;
	float p = 0;

	void Razura::update()
	{
		p -= Input::getScroll().y * 32.f;

		z = tween(z, p, Time::deltaTime * 10.f);

		if(p < 0)
			p = 0;

		if (p > 128.f)
			p = 128.f;
	}

	void Razura::render()
	{
		Graphics2D graphics;

		graphics.drawClear();
		graphics.drawSprite(sprite, vec2f(2, 128));

		graphics.setColor(color32::dkgray());
		graphics.drawString("Font rendering test `~1!2@3#4$5%6^7&8*9(0)-_=+\\][{};':\",./<>?", vec2f(0,z));
	}

	void Razura::init()
	{
		
	}

	void Razura::destroy()
	{

	}
}
