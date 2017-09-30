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
			{ "Settings",  UILoader::load("UISettings.xml") }, 
			{ "Node editor", nodeEditor }
		};

		m_UI->setRoot(std::make_shared<TabbedPanel>(p));

		for(int i = 0; i < 4; i++)
		{
			auto m = std::make_shared<Node>("Abcdefg :)");
			m->localbounds().position += Vector2i(128 * i, 0);
			m->setInputs(3);
			m->setOutputs(2);
			m->setContent(UILoader::load("UISettings.xml"));
			nodeEditor->addNode(m);
		}

	}

	void Razura::destroy()
	{ }
}
