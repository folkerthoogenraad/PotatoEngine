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
#include "potato_ui/Checkbox.h"
#include "potato_ui/Slider.h"
#include "potato_ui/Label.h"
#include "potato_ui/Dropdown.h"
#include "graphics/Renderer.h"

namespace ftec {


	void Razura::update()
	{
		ui->update();
	}


	std::shared_ptr<Light> light;

	void Razura::render()
	{
		ui->render();
	}

	void Razura::init()
	{
		ui = std::make_shared<potato::PotatoUI>();

		auto rootPanel = std::make_shared<potato::Panel>();

		ui->setRoot(rootPanel);

		auto button = std::make_shared<potato::Button>();
		auto textfield = std::make_shared<potato::TextField>();
		auto textfield2 = std::make_shared<potato::TextField>();
		auto checkbox = std::make_shared<potato::Checkbox>();
		auto slider = std::make_shared<potato::Slider>();
		auto label = std::make_shared<potato::Label>();
		auto dropdown = std::make_shared<potato::Dropdown>();

		button->text() = "Button Test!";
		textfield->hint() = "Username";
		textfield2->hint() = "Password";
		checkbox->text() = "Check this test";
		label->text() = "oi just a label brah";
		slider->setSteps(10);

		auto &options = dropdown->getTextOptions();
		options.push_back("Option 0");
		options.push_back("Option 1");
		options.push_back("Option 2");

		button->bounds() = rect2i(2, 2, 128 - 4, 32 - 4);
		textfield->bounds() = rect2i(2, 32 + 2, 512 - 4, 32 - 4);
		textfield2->bounds() = rect2i(2, 64 + 2, 512 - 4, 32 - 4);
		checkbox->bounds() = rect2i(2, 64 + 32 + 2, 128 - 4, 32 - 4);
		slider->bounds() = rect2i(2, 64 + 64 + 2, 128 - 4, 32 - 4);
		label->bounds() = rect2i(130, 64 + 64 + 2, 128 - 4, 32 - 4);
		dropdown->bounds() = rect2i(130 + 130, 2, 128 - 4, 32 - 4);

		rootPanel->bounds() = rect2i(0,0, Engine::getWindow().getWidth(), Engine::getWindow().getHeight());

		rootPanel->addPanel(button);
		rootPanel->addPanel(textfield);
		rootPanel->addPanel(textfield2);
		rootPanel->addPanel(checkbox);
		rootPanel->addPanel(slider);
		rootPanel->addPanel(label);
		rootPanel->addPanel(dropdown);
	}

	void Razura::destroy()
	{

	}
}
