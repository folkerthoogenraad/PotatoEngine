#include "XMLDocument.h"
#include <assert.h>

namespace ftec {

	namespace xml {

		std::ostream & operator<<(std::ostream & o, const XMLNode & node)
		{
			if (node.m_Type == XMLNode::Type::NODE) {
				o << "<" << node.m_Tag;

				for (auto &attrib : node.m_Attributes) {
					o << " " << attrib.first << "=\"" << attrib.second << "\"";
				}

				//If it has no children we can selfclose
				if (node.m_Children.size() == 0) {
					o << "/>";
				}
				//But if it has children, we must write them all first
				else {
					o << ">";

					for (auto &child : node.m_Children) {
						o << child;
					}

					o << "</" << node.m_Tag << ">";
				}
			}
			else {
				o << node.m_Tag;
			}
			return o;
		}

		std::ostream & operator<<(std::ostream & o, const XMLDocument & doc)
		{
			return o << doc.m_Root;
		}

		void XMLNode::setContent(const std::string & content)
		{
			assert(m_Type == Type::TEXT);
			m_Tag = content;
		}

		const std::string & XMLNode::getContent() const
		{
			assert(m_Type == Type::TEXT);
			return m_Tag;
		}

		void XMLNode::setTag(const std::string & content)
		{
			assert(m_Type == Type::NODE);
			m_Tag = content;
		}

		const std::string & XMLNode::getTag() const
		{
			assert(m_Type == Type::NODE);
			return m_Tag;
		}

		void XMLNode::setAttribute(const std::string & attribute, const std::string & value)
		{
			assert(m_Type == Type::NODE);
			m_Attributes[attribute] = value;
		}

		bool XMLNode::getAttribute(const std::string & attribute, std::string & outValue)
		{
			assert(m_Type == Type::NODE);
			auto i = m_Attributes.find(attribute);
			if (i == m_Attributes.end())
				return false;

			outValue = i->second;
			return true;
		}

		void XMLNode::addChild(const XMLNode &node)
		{
			assert(m_Type == Type::NODE);
			m_Children.push_back(node);
		}

		void XMLNode::addText(const std::string & text)
		{
			assert(m_Type == Type::NODE);
			XMLNode node(Type::TEXT);
			node.setContent(text);
			addChild(node);
		}

		const std::vector<XMLNode>& XMLNode::getChildren()
		{
			assert(m_Type == Type::NODE);
			return m_Children;
		}

		XMLNode text(const std::string text)
		{
			XMLNode node(XMLNode::Type::TEXT);
			node.m_Tag = text;
			return node;
		}

		XMLNode node(const std::string &tag, const std::map<std::string, std::string> &attributes, const std::vector<XMLNode> &nodes)
		{
			XMLNode node(XMLNode::Type::NODE);
			node.m_Tag = tag;
			node.m_Children = nodes;
			node.m_Attributes = attributes;
			return node;
		}

		std::pair<std::string, std::string> attribute(const std::string & attribute, const std::string & value)
		{
			return std::make_pair(attribute, value);
		}

	}
}
