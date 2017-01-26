#pragma once

#include "scene/Entity.h"

namespace ftec {

	class BSPEntity : public Entity{
	
	public:
		void onStart() override;
		void render() override;
	};

}