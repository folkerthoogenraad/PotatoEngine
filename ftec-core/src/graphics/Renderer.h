#pragma once

#include <vector>

namespace ftec {

	class InstanceList;
	class Mesh;

	template <typename T> struct Rectangle; typedef Rectangle<int> Rectanglei;
	template <typename T> struct Vector3; typedef Vector3<float> Vector3f;

	class Renderer {

	public:
		Renderer() = delete;

		static void drawDirect(const Mesh &mesh);
		static void drawDirect(const Mesh &mesh, const InstanceList &list);

		//Sets the clipping plane
		static void clip(const Rectanglei &rectangle);
		//Sets the viewport
		static void viewport(const Rectanglei &rectangle);

		//Sets both the viewport and the clipping plane
		static void renderport(const Rectanglei &rectangle);

		static void clear();
	};

	class InstanceList {
	private:
		unsigned int m_Vbo;
	public:
		std::vector<Vector3f> m_Positions;

		InstanceList();
		~InstanceList();

		void upload();
		
		friend Renderer;
	};
}