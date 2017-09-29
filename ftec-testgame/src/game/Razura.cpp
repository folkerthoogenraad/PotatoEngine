#include "Razura.h"

#include "graphics/Renderer.h"

#include "potato_ui/UILoader.h"

#include "potato_ui/NodeEditor.h"
#include "potato_ui/Node.h"
#include "potato_ui/TabbedPanel.h"


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
			{ "Settings",  nodeEditor }, //UILoader::load("UISettings.xml")
			{ "Other stuff", UILoader::load("UISettings.xml") }
		};

		m_UI->setRoot(std::make_shared<TabbedPanel>(p));

		{
			auto m = std::make_shared<Node>("Abcdefg :)");
			nodeEditor->addNode(m);
			m->localbounds().position += Vector2i(128, 0);
			m->setContent(UILoader::load("UISettings.xml"));
		}

		{
			auto m = std::make_shared<Node>("Jouw moeder :)");
			nodeEditor->addNode(m);
			m->localbounds().position += Vector2i(0, 0);
			m->setContent(UILoader::load("UISettings.xml"));
		}

	}

	void Razura::destroy()
	{ }
}
