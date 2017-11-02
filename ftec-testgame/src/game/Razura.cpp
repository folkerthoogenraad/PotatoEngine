#include "Razura.h"

#include "graphics/Renderer.h"

#include "potato_ui/UILoader.h"

#include "potato_ui/NodeEditor.h"
#include "potato_ui/Node.h"
#include "potato_ui/TabbedPanel.h"
#include "potato_ui/Dropdown.h"

#include "modularsynth/OscillatorNode.h"


namespace ftec {
	void Razura::update()
	{
		m_UI->update();
	}

	void Razura::render()
	{
		Renderer::clear();
		m_UI->render();
	}

	void Razura::init(std::shared_ptr<EngineContext> context)
	{
		Game::init(context);

		using namespace potato;
		m_UI = std::make_shared<PotatoUI>(context);

		auto ui = UILoader::load(context, "UISettings.xml");

		PotatoStyle style;
		ui->background() = style.m_BackgroundColor;
		ui->setOpaque(true);

		m_UI->setRoot(ui);

	}

	void Razura::destroy()
	{ }
}
