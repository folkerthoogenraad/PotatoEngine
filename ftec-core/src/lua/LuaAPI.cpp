#include "LuaAPI.h"
#include "lua.hpp"
#include "logger/log.h"

#include <vector>
#include <string>

#include "engine/Engine.h"

#define lua_namespace(name) static std::vector<std::pair<std::string, lua_CFunction>> name
#define lua_function(name) static int name (lua_State *L)
#define lua_register_function(name) std::make_pair("" #name, name)

namespace ftec {

	namespace runtime {
		
		lua_function (unimplemented) {
			LOG("Unimplemented feature!");
			return 0;
		} 

		lua_function(window_get_width) {
			lua_pushinteger(L, Engine::getWindow().getWidth());
			return 1;
		}

		lua_function(window_get_height){
			lua_pushinteger(L, Engine::getWindow().getHeight());
			return 1;
		}

		lua_namespace(lua_functions){
			lua_register_function(window_get_width),
			lua_register_function(window_get_height),
		};
	}

	void lua::bind(lua_State * L)
	{
		for (auto &pair : runtime::lua_functions) {
			lua_register(L, pair.first.c_str(), pair.second);
		}
	}
}
