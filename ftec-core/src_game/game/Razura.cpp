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

#include "potato_ui/Button.h"
#include "potato_ui/TextField.h"

namespace ftec {

	Razura::Razura()
		:sprite(Engine::getResourceManager().load<Texture>("textures/spritesheet.png"), rect2f(16, 0, 33, 33))
	{

	}


	void Razura::update()
	{
		panel.update();
	}

	void Razura::render()
	{
		graphics.begin();

		graphics.drawClear();

		panel.draw(graphics);

		graphics.end();
	}

	void Razura::init()
	{
		auto button = std::make_shared<potato::Button>();
		auto textfield = std::make_shared<potato::TextField>();
		auto textfield2 = std::make_shared<potato::TextField>();

		button->text() = "Button Test!";
		textfield->hint() = "Username";
		textfield2->hint() = "Password";

		button->bounds() = rect2i(2, 2, 128 - 4, 32 - 4);
		textfield->bounds() = rect2i(2, 32 + 2, 512 - 4, 32 - 4);
		textfield2->bounds() = rect2i(2, 64 + 2, 512 - 4, 32 - 4);

		panel.bounds() = rect2i(0,0, 512, 256);

		panel.addPanel(button);
		panel.addPanel(textfield);
		panel.addPanel(textfield2);
	}

	void Razura::destroy()
	{

	}
}
