#include "Mesh.h"
#include <fstream>
#include <string>
#include <map>
#include "logger/log.h"
#include <sstream>
#include "GL.h"

namespace ftec {
	Mesh::Mesh()
	{
		glGenBuffers(1, &m_VerticesVBO);
		glGenBuffers(1, &m_UvsVBO);
		glGenBuffers(1, &m_NormalsVBO);
		glGenBuffers(1, &m_TangentsVBO);
		glGenBuffers(1, &m_IndicesVBO);
	}

	Mesh::~Mesh()
	{
		glDeleteBuffers(1, &m_VerticesVBO);
		glDeleteBuffers(1, &m_UvsVBO);
		glDeleteBuffers(1, &m_NormalsVBO);
		glDeleteBuffers(1, &m_TangentsVBO);
		glDeleteBuffers(1, &m_IndicesVBO);
	}

	void Mesh::upload()
	{

		std::vector<vec3f> vertices;
		std::vector<vec3f> normals;
		std::vector<vec3f> tangents;
		std::vector<vec2f> uvs;
		std::vector<unsigned int> indices;

		for (int i = 0; i < m_Triangles.size(); i++) {
			FaceIndex &f = m_Triangles[i];

			vertices.push_back(m_Vertices[f.vertex]);
			normals.push_back(m_Normals[f.normal]);
			tangents.push_back(m_Tangents[f.normal]); //Tangents and normals share the index, for obvious reasons
			uvs.push_back(m_Uvs[f.uv]);

			indices.push_back(i);
		}
		//TODO lots of checks to validate the data given in the stuff here
		//TODO use buffer subdata, probably not useful in most cases here though

		if (vertices.size() == 0 || normals.size() == 0 || uvs.size() == 0 || indices.size() == 0) {
			LOG("Can't upload mesh.");
			return;//Its not gonna work now is it
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3f) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_NormalsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3f) * normals.size(), &normals[0], GL_STATIC_DRAW);
		
		glBindBuffer(GL_ARRAY_BUFFER, m_TangentsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3f) * tangents.size(), &tangents[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_UvsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec2f) * uvs.size(), &uvs[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
	}

	void Mesh::optimize()
	{
		//TODO do things like merge doubles and stuff
	}

	void Mesh::recalculateNormals()
	{
		struct vec3c {
			vec3f value = vec3f(0, 0, 0);
			int count = 0;
		};

		std::vector<vec3c> normals;

		normals.resize(m_Normals.size());

		for (int i = 0; i < m_Triangles.size(); i += 3) {
			//Fetch all the needed stuff
			FaceIndex &i0 = m_Triangles[i + 0];
			FaceIndex &i1 = m_Triangles[i + 1];
			FaceIndex &i2 = m_Triangles[i + 2];

			//p0
			//|\
			//| \
			//|  \
			//|   \
			//|____\
			//p1   p2

			const vec3f &p0 = m_Vertices[i0.vertex];
			const vec3f &p1 = m_Vertices[i1.vertex];
			const vec3f &p2 = m_Vertices[i2.vertex];

			vec3f pDelta1 = p1 - p0;
			vec3f pDelta2 = p2 - p0;
			vec3f normal = vec3f::cross(pDelta1, pDelta2).normalize();

			normals[i0.normal].value += normal;
			normals[i0.normal].count++;

			normals[i1.normal].value += normal;
			normals[i1.normal].count++;

			normals[i2.normal].value += normal;
			normals[i2.normal].count++;

		}

		for (int i = 0; i < m_Normals.size(); i ++){
			if (normals[i].count > 0) {
				m_Normals[i] = normals[i].value.normalize();
			}
		}
	}

	void Mesh::recalculateTangents()
	{
		m_Tangents.resize(m_Normals.size());

		struct vec3c {
			vec3f value = vec3f(0, 0, 0);
			int count = 0;
		};

		std::vector<vec3c> tangents;
		tangents.resize(m_Normals.size());

		for (int i = 0; i < m_Triangles.size(); i += 3) {
			//Fetch all the needed stuff
			FaceIndex &i0 = m_Triangles[i + 0];
			FaceIndex &i1 = m_Triangles[i + 1];
			FaceIndex &i2 = m_Triangles[i + 2];

			//p0
			//|\
			//| \
			//|  \
			//|   \
			//|____\
			//p1   p2

			const vec3f &v0 = m_Vertices[i0.vertex];
			const vec3f &v1 = m_Vertices[i1.vertex];
			const vec3f &v2 = m_Vertices[i2.vertex];

			const vec2f &uv0 = m_Uvs[i0.uv];
			const vec2f &uv1= m_Uvs[i1.uv];
			const vec2f &uv2 = m_Uvs[i2.uv];

			vec3f deltaPos1 = v1 - v0;
			vec3f deltaPos2 = v2 - v0;

			vec2f deltaUV1 = uv1 - uv0;
			vec2f deltaUV2 = uv2 - uv0;

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

			vec3f tangent = ((deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r).normalize();

			tangents[i0.normal].value += tangent;
			tangents[i0.normal].count++;

			tangents[i1.normal].value += tangent;
			tangents[i1.normal].count++;

			tangents[i2.normal].value += tangent;
			tangents[i2.normal].count++;

		}

		for (int i = 0; i < m_Tangents.size(); i++) {
			if (tangents[i].count > 0) {
				
				m_Tangents[i] = tangents[i].value.normalize();
			}

		}
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

		vector<FaceIndex> triangleInput;

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
				FaceIndex f[3];

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

		mesh->m_Vertices = vertexInput;
		mesh->m_Normals = normalInput;
		mesh->m_Uvs = uvInput;

		//And ofcourse change this one
		mesh->m_Triangles = triangleInput;

		mesh->optimize();
		//mesh->recalculateNormals();
		mesh->recalculateTangents();
		mesh->upload();

		return mesh;
	}
}