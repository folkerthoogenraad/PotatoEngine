#include "Serialization.h"
#include "logger/log.h"

namespace ftec {

	Serializer::Serializer(std::string fileName, uint32_t version)
		: m_Writer(fileName, std::ios::out | std::ios::binary), m_Version(version)
	{
		m_Writer.write("FTEC", 4);
		serialize(*this, version);
	}

	void serialize(Serializer &s, uint8_t d) { serialize_t(s, d); }
	void serialize(Serializer &s, uint16_t d) { serialize_t(s, d); }
	void serialize(Serializer &s, uint32_t d) { serialize_t(s, d); }
	void serialize(Serializer &s, uint64_t d) { serialize_t(s, d); }
	void serialize(Serializer &s, int8_t d) { serialize_t(s, d); }
	void serialize(Serializer &s, int16_t d) { serialize_t(s, d); }
	void serialize(Serializer &s, int32_t d) { serialize_t(s, d); }
	void serialize(Serializer &s, int64_t d) { serialize_t(s, d); }
	void serialize(Serializer &s, float d) { serialize_t(s, d); }
	void serialize(Serializer &s, double d) { serialize_t(s, d); }

	void serialize(Serializer &s, const std::string &str)
	{
		serialize(s, (uint16_t) str.length());
		s.m_Writer.write(str.c_str(), str.length());
	}

	Deserializer::Deserializer(std::string fileName)
		: m_Reader(fileName, std::ios::in | std::ios::binary) 
	{
		char c[4];
		std::string f("FTEC");
		m_Reader.read(c, 4);

		for(int i = 0; i < 4; i++)
			if (f[i] != c[i]) {
				LOG_ERROR("Not FTEC fileformat!");
				m_Reader.close();
			}

		deserialize(*this, m_Version);
	}


	void deserialize(Deserializer &s, uint8_t &d) { deserialize_t(s, d); }
	void deserialize(Deserializer &s, uint16_t &d) { deserialize_t(s, d); }
	void deserialize(Deserializer &s, uint32_t &d) { deserialize_t(s, d); }
	void deserialize(Deserializer &s, uint64_t &d) { deserialize_t(s, d); }
	void deserialize(Deserializer &s, int8_t &d) { deserialize_t(s, d); }
	void deserialize(Deserializer &s, int16_t &d) { deserialize_t(s, d); }
	void deserialize(Deserializer &s, int32_t &d) { deserialize_t(s, d); }
	void deserialize(Deserializer &s, int64_t &d) { deserialize_t(s, d); }
	void deserialize(Deserializer &s, float &d) { deserialize_t(s, d); }
	void deserialize(Deserializer &s, double &d) { deserialize_t(s, d); }

	void deserialize(Deserializer &d, std::string &s)
	{
		uint16_t length;
		deserialize(d, length);
		s.resize(length);
		d.m_Reader.read((char*) &s[0], length);

	}
}
