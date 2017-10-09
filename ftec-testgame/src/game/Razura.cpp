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

	void Razura::init()
	{
		using namespace potato;
		m_UI = std::make_shared<PotatoUI>();

		auto nodeEditor = std::make_shared<NodeEditor>();

		std::vector<std::pair<std::string, std::shared_ptr<Panel>>> p = {
			{ "Settings",  UILoader::load("UISettings.xml") }, 
			{ "Node editor", nodeEditor }
		};

		m_UI->setRoot(std::make_shared<TabbedPanel>(p));

		nodeEditor->addNode(std::make_shared<modularsynth::OscillatorNode>());
	}

	void Razura::destroy()
	{ }
}
