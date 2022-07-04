extern "C"
{
#include "lua/lapi.h"
#include "lua/lauxlib.h"
}
#include <cstdint>
#include <Windows.h>
#include <iostream>
#include <string>
/*
   this is orignally axon's/hexus's wrapper base.
   i modded it so its for lua*state so nice
   this will wrap a global and go on from there! useless ikr!
*/

void PushGlobal(lua_State* L, int index) /* technically checks the type/global and go on from there lol shitty method */
{

	int RTType = lua_type(L, index);

	if (RTType == LUA_TLIGHTUSERDATA)
	{
		lua_pushlightuserdata(L, nullptr);
	}
	if (RTType == LUA_TNIL)
	{
		lua_pushnil(L);
	}
	else if (RTType ==LUA_TNUMBER)
	{
		lua_pushnumber(L,lua_tonumber(L, index));
	}
	else if (RTType ==LUA_TBOOLEAN)
	{
		lua_pushboolean(L,lua_toboolean(L, index));
	}
	else if (RTType ==LUA_TSTRING)
	{
		lua_pushstring(L,lua_tostring(L, index));
	}
	else if (RTType ==LUA_TTHREAD)
	{
		lua_newthread(L);
	}
	else if (RTType ==LUA_TFUNCTION)
	{
		lua_pushvalue(L, index);
		lua_pushnumber(L,luaL_ref(L, LUA_REGISTRYINDEX));
		printf("not to break your skiddy bubble rewrite vanillas function bridge\n");
		//lua_pushcclosure(L, vanillaFunctionBridge, 1);
	}
	else if (RTType ==LUA_TTABLE)
	{
		lua_pushvalue(L, index);
		lua_newtable(L);
		lua_pushnil(L);
		while (lua_next(L, -2) !=LUA_TNIL)
		{
			PushGlobal( L, -2);
			PushGlobal( L, -1);
			lua_settable(L, -3);
	        lua_pop(L, 1);
		}
		lua_pop(L, 1);
	}
	else if (RTType ==LUA_TUSERDATA)
	{
		struct Userdata
		{
			int32_t reference;
		};
		int rawInstancePtr = NULL; //lua_touserdata(L, index);
		lua_rawgeti(L, LUA_REGISTRYINDEX, 0);
		if (!lua_type(L, -1))
		{
			lua_settop(L, -2);
			lua_pushvalue(L, index);
			reinterpret_cast<Userdata*>(lua_newuserdata(L, sizeof(Userdata)))->reference =luaL_ref(L, -10000);
			lua_getmetatable(L, index);
			PushGlobal(L, -1);
			lua_setfield(L, -2, "__index");
			lua_setmetatable(L, -2);
			lua_pushvalue(L, -1);
			lua_rawseti(L, -10000, rawInstancePtr);
			lua_settop(L, -2);
		}
	}
	else
	{
		lua_pushnil(L);
	}
}

void WrapGlobal(lua_State*L, const char* global)
{
	lua_getglobal(L, global); /* get the global from the input */
	PushGlobal(L, -1); /* push the type */
	lua_setglobal(L, global); /* sets the global to input */
	lua_pop(L, 1); /* pop pop pop*/
	std::cout << "Wrapped: " << global << std::endl;
}

void ToWrap(lua_State*L)
{
	std::string gl0bal;
	std::cout << "Global to Wrap: ";
	std::cin >> gl0bal;
	WrapGlobal(L, gl0bal.c_str()); /* convert it to readable format smh visual studio */
	ToWrap(L); /* keep looping func */
}

int main()
{
	lua_State* L = luaL_newstate();
	std::cout << "Got Lua State: " << L;
	std::cout << std::endl; /* split */
	ToWrap(L); /* run what to wrap */
}
