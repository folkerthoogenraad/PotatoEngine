#pragma once

#include <memory>

#include "EngineContext.h"

// TODO create application and shit
namespace ftec {

	class Game {
		std::shared_ptr<EngineContext> m_Context;
	public:
		Game();
		virtual ~Game();

		virtual void init(std::shared_ptr<EngineContext> context) { m_Context = context; };
		virtual void destroy() = 0;

		virtual void update() = 0;
		virtual void render() = 0;
		virtual bool isCloseRequested();

		std::shared_ptr<EngineContext> getContext() { return m_Context; }
		const std::shared_ptr<EngineContext> getContext() const { return m_Context; }
		virtual bool shouldSwapBuffers() const { return true; }
	};
}