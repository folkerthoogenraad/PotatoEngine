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
		if (Input::getTypedKeys().size() > 0) {
			LOG(Input::getTypedKeys());
		}
	}

	void Razura::render()
	{
		Graphics2D graphics;

		graphics.drawClear();
		graphics.drawSprite(sprite, vec2f(64, 64));

		graphics.drawString("Font rendering test `~1!2@3#4$5%6^7&8*9(0)-_=+\\][{};':\",./<>?", vec2f(16, 128));
	}

	void Razura::init()
	{
		
	}

	void Razura::destroy()
	{

	}
}
