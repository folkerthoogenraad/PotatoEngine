#pragma once

#include "math/math.h"
#include "Light.h"
#include "Material.h"
#include <memory>

namespace ftec{

	class Texture;
	class Shader;
	class Cubemap;

	struct LightSlot {
		bool enabled = false;
		Light light;
	};

	class GraphicsState {
	public:
		static const int MAX_TEXTURES = 8;
		static const int MAX_LIGHTS = 8;

		//static std::shared_ptr<Shader> m_Shader;
		static std::shared_ptr<Cubemap> m_Skybox;
		static std::shared_ptr<Material> m_Material;

		//static TextureSlot m_Textures[MAX_TEXTURES];
		static LightSlot m_Lights[MAX_LIGHTS];

		static Vector3f eyePosition;//Rename, todo

		static Matrix4f matrixModel;
		static Matrix4f matrixView;
		static Matrix4f matrixProjection;
	public:
		GraphicsState() = delete;
		~GraphicsState() = delete;

		static void prepare();

	};

}