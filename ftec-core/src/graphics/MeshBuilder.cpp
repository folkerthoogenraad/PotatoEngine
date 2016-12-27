#include "MeshBuilder.h"
namespace ftec {

	void MeshBuilder::addQuad(Mesh & mesh, const Matrix4f & center)
	{
		int index = (int) mesh.m_Vertices.size();

		mesh.m_Vertices.push_back(center.transform(Vector3f(-0.5f, -0.5f)));
		mesh.m_Vertices.push_back(center.transform(Vector3f(0.5f, -0.5f)));
		mesh.m_Vertices.push_back(center.transform(Vector3f(0.5f, 0.5f)));
		mesh.m_Vertices.push_back(center.transform(Vector3f(-0.5f, 0.5f)));

		mesh.m_Uvs.push_back(Vector2f(0, 0));
		mesh.m_Uvs.push_back(Vector2f(1, 0));
		mesh.m_Uvs.push_back(Vector2f(1, 1));
		mesh.m_Uvs.push_back(Vector2f(0, 1));

		mesh.m_Triangles.push_back(index + 0);
		mesh.m_Triangles.push_back(index + 2);
		mesh.m_Triangles.push_back(index + 1);

		mesh.m_Triangles.push_back(index + 0);
		mesh.m_Triangles.push_back(index + 3);
		mesh.m_Triangles.push_back(index + 2);
	}

	void MeshBuilder::addCube(Mesh & mesh, const Matrix4f & center)
	{
	}

	void MeshBuilder::apply(Mesh & mesh)
	{
		mesh.recalculateNormals();
		mesh.recalculateTangents();
		mesh.upload();
	}

}
