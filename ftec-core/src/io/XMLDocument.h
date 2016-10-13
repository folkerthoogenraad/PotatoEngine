#pragma once

#include <string>
#include <map>
#include <vector>
#include <ostream>

namespace ftec {

	namespace xml {

		class XMLNode {
			friend class XMLDocument;

		public:
			enum class Type {
				TEXT, NODE
			};
		private:
			Type m_Type;

			std::string m_Tag;
			std::map<std::string, std::string> m_Attributes;
			std::vector<XMLNode> m_Children;

		public:
			XMLNode(Type type) : m_Type(type) {}

			//For when the type is TEXT
			void setContent(const std::string &content);
			const std::string &getContent() const;

			//For when the type is NODE
			void setTag(const std::string &content);
			const std::string &getTag() const;

			void setAttribute(const std::string &attribute, const std::string &value);
			bool getAttribute(const std::string &attribute, std::string &outValue);		//TODO when std::optional comes around, change this

			void addChild(const XMLNode &node);
			void addText(const std::string &text);
			std::vector<XMLNode> &getChildren();
			const std::vector<XMLNode> &getChildren() const;

			friend std::ostream &operator<<(std::ostream &o, const XMLNode &node);

			friend XMLNode text(const std::string text);
			friend XMLNode node(const std::string &tag, const std::map<std::string, std::string> &attributes = {}, const std::vector<XMLNode> &nodes = {});
			friend std::pair<std::string, std::string> attribute(const std::string &attribute, const std::string &value);
		};

		class XMLDocument {
		public:
			XMLNode m_Root;

		public:
			XMLDocument() : m_Root(XMLNode::Type::NODE) {}

			friend std::ostream &operator<<(std::ostream &o, const XMLDocument &doc);
		};

		
	}
}