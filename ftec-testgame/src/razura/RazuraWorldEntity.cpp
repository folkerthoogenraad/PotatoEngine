#include "RazuraWorldEntity.h"

#include "graphics/Graphics2D.h"


namespace ftec {
	RazuraWorldEntity::RazuraWorldEntity(std::shared_ptr<EngineContext> context, Rectanglef rectangle)
		: Entity(context), m_Bounds(rectangle)
	{
	}

	RazuraWorldEntity::~RazuraWorldEntity()
	{
	}

	void RazuraWorldEntity::onStart()
	{

		
	}

	void RazuraWorldEntity::onEnd()
	{

	}


	void RazuraWorldEntity::update()
	{
		
	}

	void RazuraWorldEntity::render2D(Graphics2D &graphics)
	{
		graphics.setColor(Color32::white());
		graphics.drawRectangle(m_Bounds, true);
	}

}
