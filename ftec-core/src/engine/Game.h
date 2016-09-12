#pragma once

namespace ftec {
	class Game {
	public:
		bool m_PreventClear = false;
	public:
		Game();
		virtual ~Game();

		virtual void init() = 0;
		virtual void destroy() = 0;

		virtual void update() = 0;
		virtual void render() = 0;
		virtual bool isCloseRequested();
	};
}