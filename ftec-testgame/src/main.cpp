#include "logger/log.h"
#include "engine/Engine.h"
#include "game/Razura.h"

#include "io/XMLDocument.h"
#include "io/XMLReader.h"

#include "lua.hpp"

#define no
#define fucks
#define given(l) "" #l

void initLua(lua_State *L);

int main(void)
{
	//ftec::Engine::create<ftec::Razura>();

	no fucks given(
		this block dude,
		cpp does not give a fuck what happens here
		its like magic
	);

	ftec::Engine::create_lua("scripts/config", initLua);

	WAIT();
	return 0;
}


void initLua(lua_State *L)
{
	LOG("Initing lua..");
}