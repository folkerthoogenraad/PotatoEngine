#pragma once

#include "resources/ResourceManager.h"
#include <vector>
#include "math/vec2.h"
#include "math/vec3.h"

typedef unsigned int GLuint;

namespace ftec {
	

	class Mesh : public ManagableResource {
	private:
	public:
		struct FaceIndex { //Wow this is ugly, but whatever
			int vertex = 0, normal = 0, uv = 0;
			FaceIndex() {}
			FaceIndex(int v, int n, int u) : vertex(v), normal(n), uv(u) {}
		};

		GLuint m_VerticesVBO, m_UvsVBO, m_NormalsVBO, m_TangentsVBO, m_IndicesVBO;
		
		std::vector<vec3f> m_Vertices;
		std::vector<vec3f> m_Normals;
		std::vector<vec2f> m_Uvs;
		std::vector<vec3f> m_Tangents;

		std::vector<FaceIndex> m_Triangles;
	public:
		Mesh();
		~Mesh();

		///Uploads the current data to the graphics processor
		void upload();

		void optimize();
		void recalculateNormals();
		void recalculateTangents();

		static std::shared_ptr<Mesh> load(std::string name);
	};
}