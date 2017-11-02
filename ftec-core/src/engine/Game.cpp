#include "Game.h"

#include "Engine.h"
#include "graphics/Window.h"

namespace ftec {
	Game::Game()
	{

	}

	Game::~Game()
	{

	}

	bool Game::isCloseRequested()
	{
		return m_Context->getWindow().isCloseRequested();
	}
}
