#pragma once

#include <vector>

namespace ftec {

	enum class Tile;

	class Tilemap {
		int m_Width;
		int m_Height;

		std::vector<Tile> m_Tiles;
	public:
		Tilemap(int width, int height);
		~Tilemap();

		void setTile(int x, int y, Tile t);
		Tile getTile(int x, int y);

		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }
	};

}