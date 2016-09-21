#pragma once

#include "resources/ResourceManager.h"
#include <vector>
#include "math/vec2.h"
#include "GL.h"
#include "math/vec3.h"

namespace ftec {
	class Mesh : public ManagableResource {
	private:
		struct Face {
			int vertex, normal, uv;
		};
	public:
		GLuint m_VerticesVBO, m_UvsVBO, m_NormalsVBO, m_IndicesVBO;
		
		std::vector<vec3f> m_Vertices;
		std::vector<vec3f> m_Normals;
		std::vector<vec2f> m_Uvs;
		std::vector<unsigned int> m_Triangles;
	public:
		Mesh();
		~Mesh();

		///Uploads the current data to the graphics processor
		void upload();

		static std::shared_ptr<Mesh> load(std::string name);
	};
}