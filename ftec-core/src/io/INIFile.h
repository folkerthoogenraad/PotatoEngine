#pragma once

#include "resources/ManageableResource.h"
#include <string>
#include <vector>
#include <memory>

namespace ftec {

	class INIFile;

	class INISegment {
		INIFile *m_File;
		std::string m_Name;

		std::vector<std::pair<std::string, std::string>> m_Values;
	public:
		INISegment(std::string name);

		std::string		getString(std::string key, std::string defaultValue = "") const;
		int				getInt(std::string key, int defaultValue = -1) const;
		double			getDouble(std::string key, double defaultValue = -1.0) const;
		float			getFloat(std::string key, float defaultValue = -1.0f) const;
		bool			getBool(std::string key, bool defaultValue = false) const;

		void			insert(std::string key, std::string value);

		const std::vector<std::pair<std::string, std::string>> &getValues() const;
		const std::string &getName() const;

		friend INIFile;
	};

	class INIFile : public ManageableResource {
		std::vector<INISegment> m_Segments;
	public:
		void addSegment(INISegment segment);

		size_t getSegmentCount() const;
		const INISegment &getSegment(size_t index) const;

		const INISegment *getSegmentByName(const std::string &name) const;
		INISegment *getSegmentByName(const std::string &name);

		std::string toString() const;

		static std::shared_ptr<INIFile> load(const std::string &file);
	};
}