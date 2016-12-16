#pragma once

#include <memory>
#include <string>
#include <map>
#include "resources/ManageableResource.h"

namespace ftec {

	class ConfigurationNode;
	class ConfigurationValue;
	class ConfigurationObject;

	class ConfigurationNode{ };

	class ConfigurationValue : public ConfigurationNode {
		std::string m_Value;
	public:
		ConfigurationValue(std::string value);

		bool asInt(int &out);
		bool asFloat(float &out);
		bool asDouble(double &out);
		bool asString(std::string &out);

		const std::string &get();
		void set(std::string value);
	};

	class ConfigurationObject : public ConfigurationNode {
		std::map<std::string, ConfigurationNode> m_Nodes;
	public:

	};


	class ConfigurationFile : public ManagableResource {
		ConfigurationObject m_Root;
	public:
		static std::shared_ptr<ConfigurationFile> load(const std::string &file);
	};

}