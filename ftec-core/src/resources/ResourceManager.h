#pragma once
#include <iostream>	//for std::cout, std::cin, std::cerr
#include <memory>	//for std::shared_ptr<T>
#include <map>		//for std::map<K,V>
#include <string>	//for std::string
#include <typeinfo>	//for std::type_info

namespace ftec {
	class ManagableResource
	{

	};

	class ResourceManager {

		typedef std::map<std::string, std::shared_ptr<ManagableResource>> ResourceMap;
		typedef std::map<const std::type_info*, ResourceMap> Resources;

		Resources m_Resources;

	public:
		template <typename T>
		std::shared_ptr<T> load(const std::string &name)
		{
			const std::type_info* c = &typeid(T);

			auto map = m_Resources.find(c);

			//The resource type has never been loaded before
			if (map == m_Resources.end()) {
				ResourceMap m;
				m.insert(std::make_pair(name, T::load(name)));
				m_Resources.insert(std::make_pair(c, m));
				return std::static_pointer_cast<T>(m.find(name)->second);
			}

			//The resource type already exists
			else {
				ResourceMap &m = map->second;
				auto resource = m.find(name);

				//This resource is not yet loaded
				if (resource == m.end()) {
					m.insert(std::make_pair(name, T::load(name)));
					resource = m.find(name);

					return std::static_pointer_cast<T>(resource->second);
				}
				//This resource is loaded
				else {
					return std::static_pointer_cast<T>(resource->second);
				}
			}
		}
	};
}