#include "logger/log.h"
#include "engine/Engine.h"
#include "game/Razura.h"

#include "io/XMLDocument.h"
#include "io/XMLReader.h"

#include "lua.hpp"

void initLua(lua_State *L);

int main(void)
{
	//ftec::Engine::create<ftec::Razura>();


	ftec::Engine::create_lua("scripts/config", initLua);

	WAIT();
	return 0;
}


void initLua(lua_State *L)
{
	LOG("Initing lua..");
}