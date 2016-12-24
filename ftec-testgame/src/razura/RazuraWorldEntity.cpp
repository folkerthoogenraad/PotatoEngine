#include "RazuraWorldEntity.h"

#include "engine/Engine.h"
#include "engine/KeyCodes.h"
#include "engine/Input.h"

#include "resources/ResourceManager.h"

#include "math/Matrix4.h"
#include "math/Vector3.h"
#include "math/Vector2.h"

#include "graphics/Graphics.h"
#include "graphics/Texture.h"
#include "graphics/Mesh.h"
#include "graphics/Material.h"

#include "logger/log.h"

#include <queue>

namespace ftec {

	void RazuraWorldEntity::onStart()
	{
		remake();
	}

	void RazuraWorldEntity::onEnd()
	{

	}

	void RazuraWorldEntity::remake()
	{
		const int size = 128;
		const float bumpyness = 2.0f;

		m_Terrain = std::make_unique<Terrain>(size + 1, size + 1, 8);

		//Set corners
		m_Terrain->setHeightRaw(0, 0, 1);
		m_Terrain->setHeightRaw(size, 0, 1);
		m_Terrain->setHeightRaw(size, size, 1);
		m_Terrain->setHeightRaw(0, size, 1);

		struct DiamondSquare {
			int x, y;
			int s;
			enum {
				DIAMOND, SQUARE
			} step;

			float factor() { return s / (float) size; }
			float random() { return (rand() / (float)RAND_MAX * 2 - 1) * factor() * bumpyness; }
		};

		std::queue<DiamondSquare> data;
		data.push({
			0,0,
			size,
			DiamondSquare::DIAMOND
		});

		while (data.size() > 0) {
			auto current = data.front();
			data.pop();

			//Diamond step
			if (current.step == DiamondSquare::DIAMOND) {

				float v = (
					m_Terrain->getHeightEdgeloop(current.x, current.y) +
					m_Terrain->getHeightEdgeloop(current.x + current.s, current.y) +
					m_Terrain->getHeightEdgeloop(current.x + current.s, current.y + current.s) +
					m_Terrain->getHeightEdgeloop(current.x, current.y + current.s)
					) / 4.0f;

				m_Terrain->setHeightRaw(
					current.x + current.s / 2,
					current.y + current.s / 2,
					v + current.random()
				);

				//Add the square step
				data.push({
					current.x, current.y,
					current.s,
					DiamondSquare::SQUARE
				});
			}
			
			//Square step
			else {
				int hs = current.s / 2;
				auto sample = [&](int x, int y) {
					return (
						m_Terrain->getHeightEdgeloop(x+hs, y) +
						m_Terrain->getHeightEdgeloop(x-hs, y) +
						m_Terrain->getHeightEdgeloop(x, y+hs) +
						m_Terrain->getHeightEdgeloop(x, y-hs)
						) / 4.0f;
				};
				auto set = [&](int x, int y) {
					float s = sample(x, y);

					m_Terrain->setHeightRaw(x, y, s + current.random());
				};

				set(current.x + hs, current.y);
				set(current.x + hs, current.y + current.s);
				set(current.x, current.y + hs);
				set(current.x + current.s, current.y + hs);

				if (hs > 1) {
					data.push({
						current.x, current.y,
						hs,
						DiamondSquare::DIAMOND
					});
					data.push({
						current.x + hs, current.y,
						hs,
						DiamondSquare::DIAMOND
					});
					data.push({
						current.x + hs, current.y + hs,
						hs,
						DiamondSquare::DIAMOND
					});
					data.push({
						current.x, current.y + hs,
						hs,
						DiamondSquare::DIAMOND
					});
				}
			}
		}


		m_Terrain->create();
	}

	void RazuraWorldEntity::update()
	{
		if (Input::isKeyPressed(KEY_ENTER))
			remake();
	}

	void RazuraWorldEntity::render()
	{
		m_Terrain->render();
	}

}
