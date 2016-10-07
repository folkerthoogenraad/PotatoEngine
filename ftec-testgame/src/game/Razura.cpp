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
#include "potato_ui/LinearLayout.h"
#include "potato_ui/LayoutParams.h"
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

		auto rootPanel = std::make_shared<potato::LinearLayout>(potato::LinearLayout::VERTICAL);

		ui->setRoot(rootPanel);

		auto group = std::make_shared<potato::LinearLayout>(potato::LinearLayout::HORIZONTAL);
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

		group->layoutparams().m_WidthScaling = potato::LayoutParams::MATCH_PARENT;

		textfield->layoutparams().m_WidthScaling = potato::LayoutParams::MATCH_PARENT;

		auto &options = dropdown->getTextOptions();
		options.push_back("Option 0");
		options.push_back("Option 1");
		options.push_back("Option 2");

		group->addPanel(button);
		group->addPanel(textfield);
		group->addPanel(textfield2);

		rootPanel->addPanel(dropdown);
		rootPanel->addPanel(checkbox);
		rootPanel->addPanel(slider);
		rootPanel->addPanel(label);
		rootPanel->addPanel(group);

	}

	void Razura::destroy()
	{

	}
}
