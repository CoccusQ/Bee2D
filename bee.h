#ifndef BEE_H
#define BEE_H

#include <string.h>
#include <lua.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <SDL2/SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Color background_color;

void bee_load(lua_State* L);
void bee_update(lua_State* L, double dt);
void bee_draw(lua_State* L);
void bee_keydown(lua_State* L, SDL_Event* event);
void bee_keyup(lua_State* L, SDL_Event* event);
void bee_mousebuttondown(lua_State* L, SDL_Event* event);
void bee_mousebuttonup(lua_State* L, SDL_Event* event);
void bee_mousemove(lua_State* L, SDL_Event* event);

void register_all(lua_State* L);

#endif