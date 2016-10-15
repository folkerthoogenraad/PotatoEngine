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

		static vec3f eyePosition;//Rename, todo

		static mat4 matrixModel;
		static mat4 matrixView;
		static mat4 matrixProjection;
	public:
		GraphicsState() = delete;
		~GraphicsState() = delete;

		static void prepare();

	};

}