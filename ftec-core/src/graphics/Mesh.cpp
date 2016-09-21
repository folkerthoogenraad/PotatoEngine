#include "Mesh.h"
#include <fstream>
#include <string>
#include "logger/log.h"
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

		if (m_Vertices.size() == 0 || m_Normals.size() == 0 || m_Uvs.size() == 0 || m_Triangles.size() == 0)
			return;//Its not gonna work now is it

		glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3f) * m_Vertices.size(), &m_Vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_NormalsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3f) * m_Normals.size(), &m_Normals[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_UvsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec2f) * m_Uvs.size(), &m_Uvs[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_Triangles.size(), &m_Triangles[0], GL_STATIC_DRAW);
	}

	std::shared_ptr<Mesh> Mesh::load(std::string name)
	{
		//Currently only loads obj files, only ones with normals and uv's, and only ones with triangulated faces.
		using namespace std;

		auto mesh = make_shared<Mesh>();

		fstream input(name);

		if (!input)
			return mesh;

		vector<vec3f> vertexInput;
		vector<vec3f> normalInput;
		vector<vec2f> uvInput;

		vector<Face> triangleInput;

		//Retrieve the input

		while (input) {
			string line;
			getline(input, line);

			stringstream reader(line);

			string character;
			reader >> character;

			if (character == "v") {
				vec3f v;

				reader >> v.x;
				reader >> v.y;
				reader >> v.z;
				//std::cout << "Vertex : " << v << std::endl;

				vertexInput.push_back(v);
			}
			else if (character == "vt") {
				vec2f v;

				reader >> v.x;
				reader >> v.y;
				//std::cout << "Uv : " << v << std::endl;

				uvInput.push_back(v);
			}
			else if (character == "vn") {
				vec3f v;

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

					f[i].vertex -= 1;
					f[i].uv -= 1;
					f[i].normal -= 1;

					//std::cout << "Face: " << f[i].vertex << " / " << f[i].uv << " / " << f[i].normal << std::endl;
					triangleInput.push_back(f[i]);
				}

			}
		}
		
		//Now we just need to map it to the OpenGL way

		mesh->m_Vertices.clear(); 
		mesh->m_Normals.clear();
		mesh->m_Uvs.clear();

		//And ofcourse change this one
		mesh->m_Triangles.clear();

		for (int i = 0; i < triangleInput.size(); i++) {
			Face &f = triangleInput[i];

			//This is so far away from a good idea...
			//This should be fixed sometime (because of memory usage)
			//I should look out for s off and s on

			mesh->m_Vertices.push_back(vertexInput[f.vertex]);
			mesh->m_Normals.push_back(normalInput[f.normal]);
			mesh->m_Uvs.push_back(uvInput[f.uv]);

			mesh->m_Triangles.push_back(i);
		}

		mesh->upload();

		return mesh;
	}
}