#pragma once

#include <string>
#include <functional>
#include <map>
#include "Panel.h"
#include "io/XMLReader.h"

namespace potato {

	typedef std::function<std::shared_ptr<Panel>(ftec::xml::XMLNode&)> UILoaderFunction;
	
	class UILoader {

		static std::map<std::string, UILoaderFunction> m_Loaders;
	public:
		static void registerLoader(const std::string &tag, const UILoaderFunction &function);
		static std::shared_ptr<Panel> load(const std::string &file);
		static std::shared_ptr<Panel> load(ftec::xml::XMLDocument &doc);
		static std::shared_ptr<Panel> load(ftec::xml::XMLNode &node);

		static void loadLayoutParams(std::shared_ptr<Panel> panel, ftec::xml::XMLNode &node);
	};
}