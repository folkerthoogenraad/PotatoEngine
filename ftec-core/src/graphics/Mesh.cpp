#include "Mesh.h"
#include <fstream>
#include <string>
#include <sstream>

namespace ftec {
	Mesh::Mesh()
	{
		glGenBuffers(1, &m_VerticesVBO);
		glGenBuffers(1, &m_UvsVBO);
		glGenBuffers(1, &m_NormalsVBO);
		glGenBuffers(1, &m_IndicesVBO);
	}

	Mesh::~Mesh()
	{
		glDeleteBuffers(1, &m_VerticesVBO);
		glDeleteBuffers(1, &m_UvsVBO);
		glDeleteBuffers(1, &m_NormalsVBO);
		glDeleteBuffers(1, &m_IndicesVBO);
	}

	void Mesh::upload()
	{
		//TODO lots of checks to validate the data given in the stuff here
		//TODO use buffer subdata, probably not useful in most cases here though

		glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * m_Vertices.size(), &m_Vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_NormalsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * m_Normals.size(), &m_Normals[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_UvsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * m_Uvs.size(), &m_Uvs[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_Triangles.size(), &m_Triangles[0], GL_STATIC_DRAW);
	}

	std::shared_ptr<Mesh> Mesh::load(std::string name)
	{
		//Currently only loads obj files, only ones with normals and uv's, and only ones with triangulated faces.
		using namespace std;

		auto mesh = make_shared<Mesh>();

		fstream input(name);

		vector<vec3> vertexInput;
		vector<vec3> normalInput;
		vector<vec2> uvInput;

		vector<Face> triangleInput;

		//Retrieve the input

		while (input) {
			string line;
			getline(input, line);

			stringstream reader(line);

			string character;
			reader >> character;

			if (character == "v") {
				vec3 v;

				reader >> v.x;
				reader >> v.y;
				reader >> v.z;
				//std::cout << "Vertex : " << v << std::endl;

				vertexInput.push_back(v);
			}
			else if (character == "vt") {
				vec2 v;

				reader >> v.x;
				reader >> v.y;
				//std::cout << "Uv : " << v << std::endl;

				uvInput.push_back(v);
			}
			else if (character == "vn") {
				vec3 v;

				reader >> v.x;
				reader >> v.y;
				reader >> v.z;
				//std::cout << "Normal : " << v << std::endl;

				normalInput.push_back(v);
			}

			else if (character == "f") {
				Face f[3];

				for (int i = 0; i < 3; i++) {
					reader >> f[i].vertex;
					reader.get(); //This is bad idea, dont do this kdis
					reader >> f[i].uv;
					reader.get();
					reader >> f[i].normal;

					//std::cout << "Face: " << f[i].vertex << " / " << f[i].uv << " / " << f[i].normal << std::endl;
					triangleInput.push_back(f[i]);
				}

			}
		}
		
		//Now we just need to map it to the OpenGL way

		mesh->m_Vertices = vertexInput; //Vertices are easy luckaly :)

		//Resize normal and uv buffers
		mesh->m_Normals.resize(vertexInput.size());
		mesh->m_Uvs.resize(vertexInput.size());

		//And ofcourse change this one
		mesh->m_Triangles.resize(triangleInput.size());

		for (int i = 0; i < triangleInput.size(); i++) {
			Face &f = triangleInput[i];

			mesh->m_Normals[f.vertex - 1] = normalInput[f.normal - 1];
			mesh->m_Uvs[f.vertex - 1] = uvInput[f.uv - 1];
			mesh->m_Triangles[i] = f.vertex - 1;
		}

		mesh->upload();

		return mesh;
	}
}