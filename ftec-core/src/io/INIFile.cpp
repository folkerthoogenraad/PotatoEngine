#include "INIFile.h"

#include <sstream>
#include <fstream>

#include "logger/log.h"

namespace ftec {
	void INIFile::addSegment(INISegment segment)
	{
		segment.m_File = this;
		//TODO check for double segments with same name
		m_Segments.push_back(std::move(segment));
	}

	size_t ftec::INIFile::getSegmentCount() const
	{
		return m_Segments.size();
	}

	const INISegment& INIFile::getSegment(size_t index) const
	{
		return m_Segments[index];
	}

	const INISegment* INIFile::getSegmentByName(const std::string & name) const
	{
		for (auto &i : m_Segments) {
			if (i.getName() == name)
				return &i;
		}
		return nullptr;
	}

	INISegment * INIFile::getSegmentByName(const std::string & name)
	{
		for (auto &i : m_Segments) {
			if (i.getName() == name)
				return &i;
		}
		return nullptr;
	}

	std::string INIFile::toString() const
	{
		std::stringstream stream;

		for (auto &segment : m_Segments)
		{
			stream << "[" << segment.getName() << "]" << std::endl;

			for (const auto &i : segment.getValues())
			{
				stream << i.first << "=" << i.second << std::endl;
			}

		}

		return stream.str();
	}

	std::shared_ptr<INIFile> INIFile::load(const std::string & filepath)
	{
		std::ifstream stream(filepath);
		if (!stream)
			return nullptr;

		auto result = std::make_shared<INIFile>();
		INISegment *segment = nullptr;

		std::string line;
		while (std::getline(stream, line))
		{
			if (line.size() < 1)
				continue; //Ignore whitespace
			if (line[0] == '#')
				continue; //Ignore lines

			//Segment header
			if (line[0] == '[') {
				int closeIndex = -1;
				
				for (int i = 0; i < line.size(); i++)
					if (line[i] == ']') closeIndex = i;

				if (closeIndex < 0) {
					LOG_WARNING("Error on line : \"" << line << "\" (no close found)");
					LOG_WARNING("Assuming last index as close index");
					closeIndex = (int)line.size() - 1;
				}

				std::string header = line.substr(1, closeIndex - 1);

				result->addSegment(INISegment(header));
				segment = result->getSegmentByName(header);
			}

			//Value type
			else {
				int equalsIndex = -1;
				
				for (int i = 0; i < line.size(); i++)
					if (line[i] == '=') equalsIndex = i;

				std::string key, value;

				if (equalsIndex < 0) {
					LOG_WARNING("Error on line : \"" << line << "\" (ignoring, setting value to true)");
					key = line;
					value = "true";
				}
				else {
					key = line.substr(0, equalsIndex);
					value = line.substr(equalsIndex + 1);
				}

				if (!segment) {
					LOG_WARNING("Ignoring line : " << line << " (not attached to any header)");
					continue;
				}

				segment->insert(key, value);
			}
		}

		return result;
	}

	INISegment::INISegment(std::string name)
		: m_Name(std::move(name))
	{ }

	template <typename T>
	static T readValue(const std::vector<std::pair<std::string, std::string>> &m, const std::string &key, T defaultValue)
	{
		//TODO prevent the double tripple copying and shit
		//This function is already fucking slow
		//So don't make it any slower still.
		const std::pair<std::string, std::string> *p = nullptr;

		for (int i = 0; i < m.size(); i++) {
			if (m[i].first == key) {
				p = &m[i];
				break;
			}
		}

		if (!p)
			return defaultValue;

		std::stringstream stream(p->second);
		T result = defaultValue;

		stream >> result;

		return result;
	}

	std::string INISegment::getString(std::string key, std::string defaultValue) const
	{
		return readValue(m_Values, key, defaultValue);
	}

	int INISegment::getInt(std::string key, int defaultValue) const
	{
		return readValue(m_Values, key, defaultValue);
	}

	double INISegment::getDouble(std::string key, double defaultValue) const
	{
		return readValue(m_Values, key, defaultValue);
	}

	float INISegment::getFloat(std::string key, float defaultValue) const
	{
		return readValue(m_Values, key, defaultValue);
	}

	bool INISegment::getBool(std::string key, bool defaultValue) const
	{
		//Default behaviour parses 0 and 1 as bools, not true and false
		std::string str = getString(key, "");
		
		if (str == "true")
			return true;
		if (str == "false")
			return false;

		return defaultValue;
	}

	void INISegment::insert(std::string key, std::string value)
	{
		//TODO check of duplicates?
		m_Values.push_back({key, value});
	} 

	const std::vector<std::pair<std::string, std::string>>& INISegment::getValues() const
	{
		return m_Values;
	}

	const std::string & INISegment::getName() const
	{
		return m_Name;
	}
}