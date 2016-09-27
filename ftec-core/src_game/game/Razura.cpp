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
		Engine::getResourceManager().load<Font>("fonts/default12.fnt");
	}

	void Razura::update()
	{

	}

	void Razura::render()
	{
		Graphics2D graphics;

		graphics.drawClear();
		graphics.drawSprite(sprite, vec2f(64, 64));

		graphics.drawString("Dit is een test text {} <> 123456780 abcdefghijklmnopqrstuvwxyz áçé *-+", vec2f(16,128));
	}

	void Razura::init()
	{
		
	}

	void Razura::destroy()
	{

	}
}
