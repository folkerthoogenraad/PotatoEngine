#include "Razura.h"
#include "scene/Scene.h"
#include "engine/Engine.h"
#include "engine/Input.h"
#include "NoClipCameraEntity.h"
#include "graphics/Graphics.h"

#include "graphics/GraphicsState.h"
#include "graphics/Shader.h"

#include "graphics/Graphics2D.h"
#include "math/vec4.h"
#include "math/rect.h"
#include "graphics/Font.h"

namespace ftec {

	Razura::Razura()
		:sprite(Engine::getResourceManager().load<Texture>("textures/spritesheet.png"), rect2f(0, 0, 16, 16))
	{

	}

	std::string str;
	void Razura::update()
	{
		str += Input::getTypedKeys();
	}

	void Razura::render()
	{
		Graphics2D graphics;

		graphics.drawClear();
		graphics.drawSprite(sprite, vec2f(64, 64));

		graphics.drawString(str, vec2f(16,128));
	}

	void Razura::init()
	{
		
	}

	void Razura::destroy()
	{

	}
}
