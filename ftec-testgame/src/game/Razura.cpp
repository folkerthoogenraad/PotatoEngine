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
#include "potato_ui/SceneView.h"
#include "graphics/Renderer.h"

namespace ftec {


	void Razura::update()
	{
		ui.update();
	}


	std::shared_ptr<Light> light;

	void Razura::render()
	{
		ui.render();
	}

	void Razura::init()
	{
		auto rootPanel = std::make_shared<potato::Panel>();
		auto button = std::make_shared<potato::Button>();
		auto textfield = std::make_shared<potato::TextField>();
		auto textfield2 = std::make_shared<potato::TextField>();

		button->text() = "Button Test!";
		textfield->hint() = "Username";
		textfield2->hint() = "Password";

		button->bounds() = rect2i(2, 2, 128 - 4, 32 - 4);
		textfield->bounds() = rect2i(2, 32 + 2, 512 - 4, 32 - 4);
		textfield2->bounds() = rect2i(2, 64 + 2, 512 - 4, 32 - 4);

		rootPanel->bounds() = rect2i(0,0, Engine::getWindow().getWidth(), Engine::getWindow().getHeight());

		rootPanel->addPanel(button);
		rootPanel->addPanel(textfield);
		rootPanel->addPanel(textfield2);

		ui.setRoot(rootPanel);
	}

	void Razura::destroy()
	{

	}
}
