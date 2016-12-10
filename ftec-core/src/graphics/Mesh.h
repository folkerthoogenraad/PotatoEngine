#pragma once

#include <memory>
#include <string>
#include "resources/ManageableResource.h"

#include <vector>
#include "math/Vector2.h"
#include "math/Vector3.h"

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
		
		std::vector<Vector3f> m_Vertices;
		std::vector<Vector3f> m_Normals;
		std::vector<Vector2f> m_Uvs;
		std::vector<Vector3f> m_Tangents;

		std::vector<FaceIndex> m_Triangles;
	public:
		Mesh();
		~Mesh();

		///Uploads the current data to the graphics processor
		void upload();

		///Optimizes the mesh and removes double vertices
		void optimize();

		void recalculateNormals();
		void recalculateTangents();

		static std::shared_ptr<Mesh> load(std::string name);
	};
}