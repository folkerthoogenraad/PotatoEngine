#pragma once

#include "math/mat4.h"
#include "Light.h"
#include <memory>

namespace ftec{

	class Texture;
	class Shader;

	struct TextureSlot {
		bool enabled = false;
		std::shared_ptr<Texture> texture; //Should actually be boost::optional, but i dont use boost library right now
	};

	struct LightSlot {
		bool enabled = false;
		Light light;
	};

	class GraphicsState {
	public:
		static const int MAX_TEXTURES = 8;
		static const int MAX_LIGHTS = 8;

		//TODO wrap variables in functions
		//So that we can obviously batch some things, so that we do not have to send everything every time
		static bool m_LightEnabled;
		static bool m_TextureEnabled;

		static std::shared_ptr<Shader> m_Shader;

		static TextureSlot m_Textures[MAX_TEXTURES];
		static LightSlot m_Lights[MAX_LIGHTS];

		static mat4 matrixModel;
		static mat4 matrixView;
		static mat4 matrixProjection;
	public:
		GraphicsState() = delete;
		~GraphicsState() = delete;

		static void prepare();

	};

}