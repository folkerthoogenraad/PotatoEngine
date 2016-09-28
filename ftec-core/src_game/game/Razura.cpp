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
	std::string str = "";

	void Razura::update()
	{
		p -= Input::getScroll().y * 32.f;

		z = tween(z, p, Time::deltaTime * 10.f);

		if(p < 0)
			p = 0;

		if (p > 128.f)
			p = 128.f;

		str += Input::getKeyString();
		if (Input::isKeyTyped(GLFW_KEY_BACKSPACE))
			str = str.substr(0, str.length() - 1);

		if (Input::isKeyTyped(GLFW_KEY_ENTER))
			str += '\n';
	}

	void Razura::render()
	{
		Graphics2D graphics;

		graphics.drawClear();
		graphics.drawSprite(sprite, vec2f(2, 128));

		float x = 128;
		float y = 128;

		graphics.setLineWidth(1.f);
		graphics.setColor(color32::red());
		graphics.drawRectangle(rect2f(x, y, 16, 16), true);
		graphics.setColor(color32::blue());
		graphics.drawRectangle(rect2f(x, y, 16, 16), false);
		graphics.setColor(color32::black());
		graphics.setLineWidth(2.f);
		graphics.drawLine(vec2f(x,y), Input::getMousePosition());
		
		graphics.setColor(color32::dkgray());
		graphics.setHorizontalAlign(FontAlign::LEFT);
		graphics.setVerticalAlign(FontAlign::TOP);

		graphics.drawString(str, vec2f(1280.f/2.f,16.f + z));
	}

	void Razura::init()
	{
		
	}

	void Razura::destroy()
	{

	}
}
