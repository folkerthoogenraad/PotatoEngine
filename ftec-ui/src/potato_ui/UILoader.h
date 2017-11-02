#pragma once

#include <string>
#include <functional>
#include <map>
#include "Panel.h"
#include "io/XMLReader.h"

namespace potato {

	typedef std::function<std::shared_ptr<Panel>(std::shared_ptr<ftec::EngineContext> context, ftec::xml::XMLNode&)> UILoaderFunction;
	
	class UILoader {

		static std::map<std::string, UILoaderFunction> m_Loaders;
	public:
		static void registerLoader(const std::string &tag, const UILoaderFunction &function);
		static std::shared_ptr<Panel> load(std::shared_ptr<ftec::EngineContext> context, const std::string &file);
		static std::shared_ptr<Panel> load(std::shared_ptr<ftec::EngineContext> context, ftec::xml::XMLDocument &doc);
		static std::shared_ptr<Panel> load(std::shared_ptr<ftec::EngineContext> context, ftec::xml::XMLNode &node);

		static void loadLayoutParams(std::shared_ptr<Panel> panel, ftec::xml::XMLNode &node);
	};
}