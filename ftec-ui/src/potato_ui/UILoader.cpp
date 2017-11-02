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

	std::shared_ptr<Panel> potato::UILoader::load(std::shared_ptr<ftec::EngineContext> context, const std::string & file)
	{
		ftec::xml::XMLDocument doc;

		if (!read(file, doc))
			return nullptr;

		return load(context, doc);
	}

	std::shared_ptr<Panel> UILoader::load(std::shared_ptr<ftec::EngineContext> context, ftec::xml::XMLDocument & doc)
	{
		return load(context, doc.m_Root);
	}

	std::shared_ptr<Panel> UILoader::load(std::shared_ptr<ftec::EngineContext> context, ftec::xml::XMLNode & node)
	{
		//It shouldn't load text eitherway, but if it does, it'll crash
		auto i = m_Loaders.find(node.getTag());

		if (i != m_Loaders.end()) {
			return i->second(context, node);
		}
		else {
			return nullptr;
		}
	}

	void UILoader::loadLayoutParams(std::shared_ptr<Panel> panel, ftec::xml::XMLNode & node)
	{
		std::string value;

		//==================================================//
		// Width and height scaling
		//==================================================//

		node.getAttribute("width", value);

		if (value == "match_parent")
			panel->layoutparams().m_WidthScaling = LayoutParams::MATCH_PARENT;
		else if (value == "wrap_content")
			panel->layoutparams().m_WidthScaling = LayoutParams::WRAP_CONTENT;
		else if (value.size() > 0) {
			panel->layoutparams().m_WidthScaling = LayoutParams::EXACT;
			panel->layoutparams().m_Size.x = std::stoi(value);
		}

		node.getAttribute("height", value);

		if (value == "match_parent")
			panel->layoutparams().m_HeightScaling = LayoutParams::MATCH_PARENT;
		else if (value == "wrap_content")
			panel->layoutparams().m_HeightScaling = LayoutParams::WRAP_CONTENT;
		else if (value.size() > 0) {
			panel->layoutparams().m_HeightScaling = LayoutParams::EXACT;
			panel->layoutparams().m_Size.y = std::stoi(value);
		}

		//==================================================//
		// Weighting scaling
		//==================================================//
		value = "";
		node.getAttribute("weight", value);
		if (value.size() > 0) {
			panel->layoutparams().m_Weight = (float)std::stoi(value);
		}

		value = "";
		if (node.getAttribute("id", value)) {
			panel->setID(value);
		}

		//==================================================//
		// Grid layout stuff
		//==================================================//

		value = "";
		if (node.getAttribute("grid_position", value)) {
			if (value == "auto") {
				panel->layoutparams().m_GridAutoLayout = true;
			}
			else {
				panel->layoutparams().m_GridAutoLayout = false;
			}
		}
		else {
			panel->layoutparams().m_GridAutoLayout = false;
		}

		value = "";
		if (node.getAttribute("grid_x", value)) {
			panel->layoutparams().m_GridLayoutRectangle.x() = std::stoi(value);
		}
		value = "";
		if (node.getAttribute("grid_y", value)) {
			panel->layoutparams().m_GridLayoutRectangle.y() = std::stoi(value);
		}
		value = "";
		if (node.getAttribute("grid_width", value)) {
			panel->layoutparams().m_GridLayoutRectangle.width() = std::stoi(value);
		}
		value = "";
		if (node.getAttribute("grid_height", value)) {
			panel->layoutparams().m_GridLayoutRectangle.height() = std::stoi(value);
		}
	}

	static std::map<std::string, UILoaderFunction> getDefaultLoaders()
	{
		std::map<std::string, UILoaderFunction> out;

		out["LinearLayout"] = [](std::shared_ptr<ftec::EngineContext> context, ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			std::string value;
			node.getAttribute("orientation", value);

			auto panel = std::make_shared<LinearLayout>(context, value == "vertical" ? LinearLayout::VERTICAL : LinearLayout::HORIZONTAL);

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			for (auto &child : node.getChildren()) {
				auto c = UILoader::load(context, child);
				if (c) {
					panel->addPanel(c);
				}
			}

			return panel;
		};

		out["Button"] = [](std::shared_ptr<ftec::EngineContext> context, ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			auto panel = std::make_shared<Button>(context);
			
			std::string value;
			node.getAttribute("text", value);

			panel->text() = value;

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			return panel;
		};

		out["TextField"] = [](std::shared_ptr<ftec::EngineContext> context, ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			auto panel = std::make_shared<TextField>(context);

			std::string value;
			node.getAttribute("hint", value);

			panel->hint() = value;

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			return panel;
		};

		out["Label"] = [](std::shared_ptr<ftec::EngineContext> context, ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			auto panel = std::make_shared<Label>(context);

			std::string value;
			node.getAttribute("text", value);

			panel->text() = value;

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			return panel;
		};
		
		out["Checkbox"] = [](std::shared_ptr<ftec::EngineContext> context, ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			auto panel = std::make_shared<Checkbox>(context);

			std::string value;
			node.getAttribute("checked", value);

			panel->setChecked(value == "true");

			node.getAttribute("text", value);

			panel->text() = value;

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			return panel;
		};

		out["NodeEditor"] = [](std::shared_ptr<ftec::EngineContext> context, ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			auto panel = std::make_shared<NodeEditor>(context);

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			return panel;
		};

		out["Slider"] = [](std::shared_ptr<ftec::EngineContext> context, ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			auto panel = std::make_shared<Slider>(context);

			std::string value;
			node.getAttribute("steps", value);

			if (value.size() > 0) {//TODO better conversion between this stuff
				panel->setSteps(std::stoi(value));
			}

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			return panel;
		};

		out["Dropdown"] = [](std::shared_ptr<ftec::EngineContext> context, ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			auto panel = std::make_shared<Dropdown>(context);

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			return panel;
		};


		out["Knob"] = [](std::shared_ptr<ftec::EngineContext> context, ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			auto panel = std::make_shared<Knob>(context);

			std::string value;
			node.getAttribute("steps", value);

			if (value.size() > 0) {//TODO better conversion between this stuff
				panel->setSteps(std::stoi(value));
			}

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			return panel;
		};

		out["SceneView"] = [](std::shared_ptr<ftec::EngineContext> context, ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
		{
			auto panel = std::make_shared<SceneView>(context);

			//Load the layout params
			UILoader::loadLayoutParams(panel, node);

			return panel;
		};

		return out;
	}
}
