#include "Tilemap.h"
#include "Tile.h"

namespace ftec {
	Tilemap::Tilemap(int width, int height)
		:m_Width(width), m_Height(height)
	{
		m_Tiles.resize(m_Width * m_Height);
	}

	Tilemap::~Tilemap()
	{
	}

	void Tilemap::setTile(int x, int y, Tile t)
	{
		m_Tiles[x + y * m_Width] = t;
	}

	Tile Tilemap::getTile(int x, int y)
	{
		if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
			return Tile::VOID;
		return m_Tiles[x + y * m_Width];
	}
}
