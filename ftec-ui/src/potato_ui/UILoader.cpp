#include "UILoader.h"

#include "LinearLayout.h"
#include "Button.h"
#include "TextField.h"
#include "SceneView.h"
#include "Label.h"
#include "Slider.h"
#include "Checkbox.h"
#include "NodeEditor.h"
#include "Knob.h"
#include "Dropdown.h"

namespace potato {

	static std::map<std::string, UILoaderFunction> getDefaultLoaders();
	
	std::map<std::string, UILoaderFunction> UILoader::m_Loaders = getDefaultLoaders();

	void UILoader::registerLoader(const std::string & tag, const UILoaderFunction &function)
	{
		m_Loaders[tag] = function;
	}

	std::shared_ptr<Panel> potato::UILoader::load(const std::string & file)
	{
		ftec::xml::XMLDocument doc;

		if (!read(file, doc))
			return nullptr;

		return load(doc);
	}

	std::shared_ptr<Panel> UILoader::load(ftec::xml::XMLDocument & doc)
	{
		return load(doc.m_Root);
	}

	std::shared_ptr<Panel> UILoader::load(ftec::xml::XMLNode & node)
	{
		//It shouldn't load text eitherway, but if it does, it'll crash
		auto i = m_Loaders.find(node.getTag());

		if (i != m_Loaders.end()) {
			return i->second(node);
		}
		else {
			return nullptr;
		}
	}

	void UILoader::loadLayoutParams(std::shared_ptr<Panel> panel, ftec::xml::XMLNode & node)
	{
		std::string value;
		
		//Width scaling
		node.getAttribute("width", value);

		if (value == "match_parent")
			panel->layoutparams().m_WidthScaling = LayoutParams::MATCH_PARENT;
		else if (value == "wrap_content")
			panel->layoutparams().m_WidthScaling = LayoutParams::WRAP_CONTENT;
		else if(value.size() > 0){
			panel->layoutparams().m_WidthScaling = LayoutParams::EXACT;
			panel->layoutparams().m_Size.x = std::stoi(value);
		}

		//Height scaling
		node.getAttribute("height", value);

		if (value == "match_parent")
			panel->layoutparams().m_HeightScaling = LayoutParams::MATCH_PARENT;
		else if (value == "wrap_content")
			panel->layoutparams().m_HeightScaling = LayoutParams::WRAP_CONTENT;
		else if (value.size() > 0) {
			panel->layoutparams().m_HeightScaling = LayoutParams::EXACT;
			panel->layoutparams().m_Size.y = std::stoi(value);
		}

		//Weighting scaling
		value = "";
		node.getAttribute("weight", value);
		if (value.size() > 0) {
			panel->layoutparams().m_Weight = (float)std::stoi(value);
		}

		if (node.getAttribute("id", value)) {
			panel->setID(value);
		}
	}

	static std::map<std::string, UILoaderFunction> getDefaultLoaders()
	{
		std::map<std::string, UILoaderFunction> out;

		out["LinearLayout"] = [](ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			std::string value;
			node.getAttribute("orientation", value);

			auto panel = std::make_shared<LinearLayout>(value == "vertical" ? LinearLayout::VERTICAL : LinearLayout::HORIZONTAL);

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			for (auto &child : node.getChildren()) {
				auto c = UILoader::load(child);
				if (c) {
					panel->addPanel(c);
				}
			}

			return panel;
		};

		out["Button"] = [](ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			auto panel = std::make_shared<Button>();
			
			std::string value;
			node.getAttribute("text", value);

			panel->text() = value;

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			return panel;
		};

		out["TextField"] = [](ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			auto panel = std::make_shared<TextField>();

			std::string value;
			node.getAttribute("hint", value);

			panel->hint() = value;

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			return panel;
		};

		out["Label"] = [](ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			auto panel = std::make_shared<Label>();

			std::string value;
			node.getAttribute("text", value);

			panel->text() = value;

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			return panel;
		};
		
		out["Checkbox"] = [](ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			auto panel = std::make_shared<Checkbox>();

			std::string value;
			node.getAttribute("checked", value);

			panel->setChecked(value == "true");

			node.getAttribute("text", value);

			panel->text() = value;

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			return panel;
		};

		out["NodeEditor"] = [](ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			auto panel = std::make_shared<NodeEditor>();

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			return panel;
		};

		out["Slider"] = [](ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			auto panel = std::make_shared<Slider>();

			std::string value;
			node.getAttribute("steps", value);

			if (value.size() > 0) {//TODO better conversion between this stuff
				panel->setSteps(std::stoi(value));
			}

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			return panel;
		};

		out["Dropdown"] = [](ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			auto panel = std::make_shared<Dropdown>();

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			return panel;
		};


		out["Knob"] = [](ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			auto panel = std::make_shared<Knob>();

			std::string value;
			node.getAttribute("steps", value);

			if (value.size() > 0) {//TODO better conversion between this stuff
				panel->setSteps(std::stoi(value));
			}

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			return panel;
		};

		out["SceneView"] = [](ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			auto panel = std::make_shared<SceneView>();

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			return panel;
		};

		return out;
	}
}
