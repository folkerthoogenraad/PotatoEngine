#include "ConfigurationFile.h"
namespace ftec {

	std::shared_ptr<ConfigurationFile> ftec::ConfigurationFile::load(const std::string & file)
	{
		auto cf = std::make_shared<ConfigurationFile>();



		return cf;
	}

	ConfigurationValue::ConfigurationValue(std::string value)
		:m_Value(std::move(value)) { }

	bool ConfigurationValue::asInt(int & out)
	{
		try {
			out = std::stoi(m_Value);
			return true;
		}
		catch (std::invalid_argument){
			return false;
		}
	}

	bool ConfigurationValue::asFloat(float & out)
	{
		try {
			out = std::stof(m_Value);
			return true;
		}
		catch (std::invalid_argument) {
			return false;
		}
	}

	bool ConfigurationValue::asDouble(double & out)
	{
		try {
			out = std::stod(m_Value);
			return true;
		}
		catch (std::invalid_argument) {
			return false;
		}
	}

	bool ConfigurationValue::asString(std::string & out)
	{
		out = m_Value;
		return true;
	}

	const std::string & ConfigurationValue::get()
	{
		return m_Value;
	}

	void ConfigurationValue::set(std::string value)
	{
		m_Value = std::move(value);
	}

}