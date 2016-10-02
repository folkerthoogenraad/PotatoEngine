#pragma once

#include <fstream>
#include <stdint.h>

namespace ftec {


	class Serializer {
		std::ofstream m_Writer;
		uint32_t m_Version;
	public:
		Serializer(std::string fileName, uint32_t version);
		~Serializer() = default;

		inline uint32_t getVersion() { return m_Version; }
		void close() { m_Writer.close(); }

		template <typename T>
		friend void serialize_t(Serializer &s, T d)
		{
			s.m_Writer.write((char*)&d, sizeof(T));
		}

		friend void serialize(Serializer &, uint8_t);
		friend void serialize(Serializer &, uint16_t);
		friend void serialize(Serializer &, uint32_t);
		friend void serialize(Serializer &, uint64_t);
		friend void serialize(Serializer &, int8_t);
		friend void serialize(Serializer &, int16_t);
		friend void serialize(Serializer &, int32_t);
		friend void serialize(Serializer &, int64_t);
		friend void serialize(Serializer &, float);
		friend void serialize(Serializer &, double);
		friend void serialize(Serializer &, const std::string &);
	};

	class Deserializer {
		std::ifstream m_Reader;
		uint32_t m_Version;
	public:
		Deserializer(std::string fileName);
		~Deserializer() = default;

		template <typename T>
		friend void deserialize_t(Deserializer &s, T &d)
		{
			s.m_Reader.read((char*)&d, sizeof(T));
		}

		friend void deserialize(Deserializer &, uint8_t&);
		friend void deserialize(Deserializer &, uint16_t&);
		friend void deserialize(Deserializer &, uint32_t&);
		friend void deserialize(Deserializer &, uint64_t&);
		friend void deserialize(Deserializer &, int8_t&);
		friend void deserialize(Deserializer &, int16_t&);
		friend void deserialize(Deserializer &, int32_t&);
		friend void deserialize(Deserializer &, int64_t&);
		friend void deserialize(Deserializer &, float&);
		friend void deserialize(Deserializer &, double&);
		friend void deserialize(Deserializer &, std::string&);

		inline uint32_t getVersion() { return m_Version; }
		void close() {m_Reader.close(); };
	};
}

