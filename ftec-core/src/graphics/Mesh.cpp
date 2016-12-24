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
		//TODO lots of checks to validate the data given in the stuff here
		//TODO use buffer subdata, probably not useful in most cases here though

		if (m_Vertices.size() == 0 || m_Normals.size() == 0 || m_Uvs.size() == 0 || m_Triangles.size() == 0) {
			LOG("Can't upload mesh.");
			return;//Its not gonna work now is it
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f) * m_Vertices.size(), &m_Vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_NormalsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f) * m_Normals.size(), &m_Normals[0], GL_STATIC_DRAW);
		
		glBindBuffer(GL_ARRAY_BUFFER, m_TangentsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f) * m_Tangents.size(), &m_Tangents[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_UvsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2f) * m_Uvs.size(), &m_Uvs[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_Triangles.size(), &m_Triangles[0], GL_STATIC_DRAW);
	}

	void Mesh::optimize()
	{
		//TODO do things like merge doubles and stuff
	}

	void Mesh::recalculateNormals()
	{
		m_Normals.clear();
		m_Normals.resize(m_Vertices.size());

		for (int i = 0; i < m_Triangles.size(); i += 3) {
			//Fetch all the needed stuff
			int i0 = m_Triangles[i + 0];
			int i1 = m_Triangles[i + 1];
			int i2 = m_Triangles[i + 2];

			//p0
			//|\
			//| \
			//|  \
			//|   \
			//|____\
			//p1   p2

			const Vector3f &p0 = m_Vertices[i0];
			const Vector3f &p1 = m_Vertices[i1];
			const Vector3f &p2 = m_Vertices[i2];

			Vector3f pDelta1 = p1 - p0;
			Vector3f pDelta2 = p2 - p0;
			Vector3f normal = Vector3f::cross(pDelta1, pDelta2).normalize();

			m_Normals[i0] += normal;
			m_Normals[i1] += normal;
			m_Normals[i2] += normal;

		}

		for (int i = 0; i < m_Normals.size(); i ++){
			if (m_Normals[i].magnitude() > 0) {
				m_Normals[i].normalize();
			}
		}
	}

	void Mesh::recalculateTangents()
	{
		std::vector<Vector3f> tangents;
		
		m_Tangents.resize(m_Normals.size());
		tangents.resize(m_Normals.size());

		for (int i = 0; i < m_Triangles.size(); i += 3) {
			//Fetch all the needed stuff
			int i0 = m_Triangles[i + 0];
			int i1 = m_Triangles[i + 1];
			int i2 = m_Triangles[i + 2];

			//p0
			//|\
			//| \
			//|  \
			//|   \
			//|____\
			//p1   p2

			const Vector3f &v0 = m_Vertices[i0];
			const Vector3f &v1 = m_Vertices[i1];
			const Vector3f &v2 = m_Vertices[i2];

			const Vector2f &uv0 = m_Uvs[i0];
			const Vector2f &uv1= m_Uvs[i1];
			const Vector2f &uv2 = m_Uvs[i2];

			Vector3f deltaPos1 = v1 - v0;
			Vector3f deltaPos2 = v2 - v0;

			Vector2f deltaUV1 = uv1 - uv0;
			Vector2f deltaUV2 = uv2 - uv0;

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

			Vector3f tangent = ((deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r).normalize();

			tangents[i0] += tangent;
			tangents[i1] += tangent;
			tangents[i2] += tangent;
		}

		for (int i = 0; i < m_Tangents.size(); i++) {
			if (tangents[i].magnitude() > 0) {
				m_Tangents[i] = tangents[i].normalize();
			}

		}
	}

	std::shared_ptr<Mesh> Mesh::load(std::string name)
	{
		//Currently only loads obj files, only ones with normals and uv's, and only ones with triangulated faces.
		using namespace std;

		struct FaceIndex { //Wow this is ugly, but whatever
			int vertex = 0, normal = 0, uv = 0;
			FaceIndex() {}
			FaceIndex(int v, int n, int u) : vertex(v), normal(n), uv(u) {}
		};

		auto mesh = make_shared<Mesh>();

		fstream input(name);

		if (!input)
			return mesh;

		vector<Vector3f> vertexInput;
		vector<Vector3f> normalInput;
		vector<Vector2f> uvInput;

		vector<FaceIndex> triangleInput;

		//Retrieve the input

		while (input) {
			string line;
			getline(input, line);

			stringstream reader(line);

			string character;
			reader >> character;

			if (character == "v") {
				Vector3f v;

				reader >> v.x;
				reader >> v.y;
				reader >> v.z;
				//std::cout << "Vertex : " << v << std::endl;

				vertexInput.push_back(v);
			}
			else if (character == "vt") {
				Vector2f v;

				reader >> v.x;
				reader >> v.y;
				//std::cout << "Uv : " << v << std::endl;

				uvInput.push_back(v);
			}
			else if (character == "vn") {
				Vector3f v;

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

		/*mesh->m_Vertices = vertexInput;
		mesh->m_Normals = normalInput;
		mesh->m_Uvs = uvInput;*/

		for (int i = 0; i < triangleInput.size(); i++) {
			FaceIndex &f = triangleInput[i];

			//Inefficient as fuck, but doesn't matter.

			mesh->m_Vertices.push_back(vertexInput[f.vertex]);
			mesh->m_Normals.push_back(normalInput[f.normal]);
			mesh->m_Uvs.push_back(uvInput[f.uv]);

			mesh->m_Triangles.push_back(i);
		}

		mesh->optimize();
		//mesh->recalculateNormals();
		mesh->recalculateTangents();
		mesh->upload();

		return mesh;
	}
}