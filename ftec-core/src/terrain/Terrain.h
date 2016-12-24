#pragma once

#include <memory>
#include <vector>

namespace ftec {

	class Mesh;

	//TODO lod levels and shit, obviously
	//TODO Think of great ways to hide seams and shit :D
	
	//NOTE i could also just have one mesh for each lod level
	//

	class Terrain {
		int m_Width, m_Height;
		float m_Resolution;
		
		//This should be devided into TerrainChunks
		//Every terrainchunk should have a TerrainLOD
		//So the rendering can do stuff, but this
		//is still just a bit of bootstrapping code and shit

		std::shared_ptr<Mesh> m_Mesh; //TODO see comment
		std::vector<float> m_Data;

	public:
		Terrain(int width, int height, float resolution = 1);

		void create();

		void render();

		float getHeightRaw(int x, int y);
		float getHeightEdgeloop(int x, int y);
		void setHeightRaw(int x, int y, float value);

		//Resolution in tiles per meter
		inline float getResolution() const { return m_Resolution; };

		inline float getTileSize() const { return 1.0f / m_Resolution; }

		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }
	};


	//Also, for great terrain rendering, I might try something with
	//Multiple camera's rendering the scene, 0.01 to 100, 100 to 1000000 
	//(Logarithmicly the same distance.) so i can render lots of terrian
	//in the far far distance.


}