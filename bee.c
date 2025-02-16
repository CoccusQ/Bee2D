#include "bee.h"

static int bee_empty(lua_State* L) { return 0; }

/*FIXME:*/
static void SDL_RenderDrawCircle(int x, int y, int radius) {
    int dx = 0, dy = radius;
    int e = 1 - radius;
    while (dx <= dy) {
        SDL_RenderDrawPoint(renderer, x + dx, y + dy);
        SDL_RenderDrawPoint(renderer, x + dx, y - dy);
        SDL_RenderDrawPoint(renderer, x - dx, y + dy);
        SDL_RenderDrawPoint(renderer, x - dx, y - dy);
        SDL_RenderDrawPoint(renderer, x + dy, y + dx);
        SDL_RenderDrawPoint(renderer, x + dy, y - dx);
        SDL_RenderDrawPoint(renderer, x - dy, y + dx);
        SDL_RenderDrawPoint(renderer, x - dy, y - dx);

        if (e < 0) {
            e += 2 * dx + 1;
        } else {
            e += 2 * (dx - dy) + 1;
            dy--;
        }
        dx++;
    }
}
/*FIXME:*/
static void SDL_RenderFillCircle(int x, int y, int radius) {
    int dx = 0, dy = radius;
    int e = 1 - radius;
    while (dx <= dy) {
        SDL_RenderDrawLine(renderer, x + dx, y + dy, x + dx, y - dy);
        SDL_RenderDrawLine(renderer, x + dx, y + dy, x - dx, y + dy);
        SDL_RenderDrawLine(renderer, x - dx, y - dy, x + dx, y - dy);
        SDL_RenderDrawLine(renderer, x - dx, y - dy, x - dx, y + dy);
        SDL_RenderDrawLine(renderer, x + dy, y + dx, x + dy, y - dx);
        SDL_RenderDrawLine(renderer, x + dy, y + dx, x - dy, y + dx);
        SDL_RenderDrawLine(renderer, x - dy, y - dx, x + dy, y - dx);
        SDL_RenderDrawLine(renderer, x - dy, y - dx, x - dy, y + dx);

        if (e < 0) {
            e += 2 * dx + 1;
        }
        else {
            e += 2 * (dx - dy) + 1;
            dy--;
        }
        dx++;
    }
}

void bee_load(lua_State* L) {
    lua_getglobal(L, "bee");
    lua_getfield(L, -1, "load");

    if (!lua_isfunction(L, -1)) {
        SDL_Log("Failed to call 'bee.load': not a lua function.");
        lua_close(L);
        return;
    }

    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
        SDL_Log("Failed to call function 'bee.load': %s", lua_tostring(L, -1));
        lua_close(L);
        return;
    }

    lua_pop(L, 1);
}

void bee_update(lua_State* L, double dt) {
    lua_getglobal(L, "bee");
    lua_getfield(L, -1, "update");

    if (!lua_isfunction(L, -1)) {
        SDL_Log("Failed to call 'bee.update': not a lua function.");
        lua_close(L);
        return;
    }

    lua_pushnumber(L, dt);

    if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
        SDL_Log("Failed to call function 'bee.update': %s", lua_tostring(L, -1));
        lua_close(L);
        return;
    }

    lua_pop(L, 1);
}

void bee_draw(lua_State* L) {
    lua_getglobal(L, "bee");
    lua_getfield(L, -1, "draw");

    if (!lua_isfunction(L, -1)) {
        SDL_Log("Failed to call 'bee.draw': not a lua function.");
        lua_close(L);
        return;
    }

    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
        SDL_Log("Failed to call function 'bee.draw': %s", lua_tostring(L, -1));
        lua_close(L);
        return;
    }

    lua_pop(L, 1);
}

void bee_keydown(lua_State* L, SDL_Event* event) {
    lua_getglobal(L, "bee");
    lua_getfield(L, -1, "keydown");

    if (!lua_isfunction(L, -1)) {
        SDL_Log("Failed to call 'bee.keydown': not a lua function.");
        lua_close(L);
        return;
    }

    lua_pushinteger(L, event->key.keysym.scancode);

    if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
        SDL_Log("Failed to call function 'bee.keydown': %s", lua_tostring(L, -1));
        lua_close(L);
        return;
    }

    lua_pop(L, 1);
}

void bee_keyup(lua_State* L, SDL_Event* event) {
    lua_getglobal(L, "bee");
    lua_getfield(L, -1, "keyup");

    if (!lua_isfunction(L, -1)) {
        SDL_Log("Failed to call 'bee.keyup': not a lua function.");
        lua_close(L);
        return;
    }

    lua_pushinteger(L, event->key.keysym.scancode);

    if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
        SDL_Log("Failed to call function 'bee.keyup': %s", lua_tostring(L, -1));
        lua_close(L);
        return;
    }

    lua_pop(L, 1);
}

void bee_mousebuttondown(lua_State* L, SDL_Event* event) {
    lua_getglobal(L, "bee");
    lua_getfield(L, -1, "mousedown");

    if (!lua_isfunction(L, -1)) {
        SDL_Log("Failed to call 'bee.mousedown': not a lua function.");
        lua_close(L);
        return;
    }

    lua_pushinteger(L, event->button.x);
    lua_pushinteger(L, event->button.y);
    lua_pushinteger(L, event->button.button);

    if (lua_pcall(L, 3, 0, 0) != LUA_OK) {
        SDL_Log("Failed to call function 'bee.mousedown': %s", lua_tostring(L, -1));
        lua_close(L);
        return;
    }

    lua_pop(L, 1);
}

void bee_mousebuttonup(lua_State* L, SDL_Event* event) {
    lua_getglobal(L, "bee");
    lua_getfield(L, -1, "mouseup");

    if (!lua_isfunction(L, -1)) {
        SDL_Log("Failed to call 'bee.mouseup': not a lua function.");
        lua_close(L);
        return;
    }

    lua_pushinteger(L, event->button.x);
    lua_pushinteger(L, event->button.y);
    lua_pushinteger(L, event->button.button);

    if (lua_pcall(L, 3, 0, 0) != LUA_OK) {
        SDL_Log("Failed to call function 'bee.mouseup': %s", lua_tostring(L, -1));
        lua_close(L);
        return;
    }

    lua_pop(L, 1);
}

void bee_mousemove(lua_State* L, SDL_Event* event) {
    lua_getglobal(L, "bee");
    lua_getfield(L, -1, "mousemove");

    if (!lua_isfunction(L, -1)) {
        SDL_Log("Failed to call 'bee.mousemove': not a lua function.");
        lua_close(L);
        return;
    }

    lua_pushinteger(L, event->button.x);
    lua_pushinteger(L, event->button.y);
    lua_pushinteger(L, event->button.button);

    if (lua_pcall(L, 3, 0, 0) != LUA_OK) {
        SDL_Log("Failed to call function 'bee.mousemove': %s", lua_tostring(L, -1));
        lua_close(L);
        return;
    }

    lua_pop(L, 1);
}

static void register_bee(lua_State* L) {
    lua_newtable(L);

    luaL_Reg bee_funcs[] = {
        {"load", bee_empty},
        {"update", bee_empty},
        {"draw", bee_empty},
        {"keydown", bee_empty},
        {"keyup", bee_empty},
        {"mousedown", bee_empty},
        {"mouseup", bee_empty},
        {"mousemove", bee_empty},
        {NULL, NULL}
    };

    luaL_setfuncs(L, bee_funcs, 0);

    lua_setglobal(L, "bee");
}

static int bee_graphics_getcolor(lua_State* L) {
    SDL_Color color;
    SDL_GetRenderDrawColor(renderer, &color.r, &color.g, &color.b, &color.r);
    lua_pushinteger(L, color.r);
    lua_pushinteger(L, color.g);
    lua_pushinteger(L, color.b);
    lua_pushinteger(L, color.a);
    return 4;
}

static int bee_graphics_getbkcolor(lua_State* L) {
    lua_pushinteger(L, background_color.r);
    lua_pushinteger(L, background_color.g);
    lua_pushinteger(L, background_color.b);
    lua_pushinteger(L, background_color.a);
    return 4;
}

static int bee_graphics_setcolor(lua_State* L) {
    SDL_Color color;
    color.r = luaL_checkinteger(L, 1);
    color.g = luaL_checkinteger(L, 2);
    color.b = luaL_checkinteger(L, 3);
    color.a = luaL_optinteger(L, 4, 255);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    return 0;
}

static int bee_graphics_setbkcolor(lua_State* L) {
    background_color.r = luaL_checkinteger(L, 1);
    background_color.g = luaL_checkinteger(L, 2);
    background_color.b = luaL_checkinteger(L, 3);
    background_color.a = luaL_optinteger(L, 4, 255);
    return 0;
}

static int bee_graphics_point(lua_State* L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    SDL_RenderDrawPoint(renderer, x, y);
    return 0;
}

static int bee_graphics_line(lua_State* L) {
    int x1 = luaL_checkinteger(L, 1);
    int y1 = luaL_checkinteger(L, 2);
    int x2 = luaL_checkinteger(L, 3);
    int y2 = luaL_checkinteger(L, 4);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    return 0;
}

static int bee_graphics_rect(lua_State* L) {
    SDL_Rect rect;
    rect.x = luaL_checkinteger(L, 1);
    rect.y = luaL_checkinteger(L, 2);
    rect.w = luaL_checkinteger(L, 3);
    rect.h = luaL_checkinteger(L, 4);
    const char* mode = luaL_optstring(L, 5, "line");
    if (strcmp(mode, "fill") == 0) {
        SDL_RenderFillRect(renderer, &rect);
    } else {
        SDL_RenderDrawRect(renderer, &rect);
    }
    return 0;
}

static int bee_graphics_circle(lua_State* L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int r = luaL_checkinteger(L, 3);
    const char* mode = luaL_optstring(L, 4, "line");
    if (strcmp(mode, "fill") == 0) {
        SDL_RenderFillCircle(x, y, r);
    } else {
        SDL_RenderDrawCircle(x, y, r);
    }
    return 0;
}

static void register_bee_graphics(lua_State* L) {
    lua_getglobal(L, "bee");

    if (!lua_istable(L, -1)) {
        SDL_Log("Failed to find 'bee' table.");
        lua_close(L);
        return;
    }

    lua_newtable(L);

    luaL_Reg bee_graphics_funcs[] = {
        {"getColor", bee_graphics_getcolor},
        {"getBackgroundColor", bee_graphics_getbkcolor},
        {"setColor", bee_graphics_setcolor},
        {"setBackgroundColor", bee_graphics_setbkcolor},
        {"point", bee_graphics_point},
        {"line", bee_graphics_line},
        {"rect", bee_graphics_rect},
        {"circle", bee_graphics_circle},
        {NULL, NULL}
    };

    luaL_setfuncs(L, bee_graphics_funcs, 0);

    lua_setfield(L, -2, "graphics");
}

static int bee_window_getsize(lua_State* L) {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    lua_pushinteger(L, w);
    lua_pushinteger(L, h);
    return 2;
}

static int bee_window_getwidth(lua_State* L) {
    int w;
    SDL_GetWindowSize(window, &w, NULL);
    lua_pushinteger(L, w);
    return 1;
}

static int bee_window_getheight(lua_State* L) {
    int h;
    SDL_GetWindowSize(window, NULL, &h);
    lua_pushinteger(L, h);
    return 1;
}

static int bee_window_setsize(lua_State* L) {
    int w = luaL_checkinteger(L, 1);
    int h = luaL_checkinteger(L, 2);
    SDL_SetWindowSize(window, w, h);
    return 0;
}

static void register_bee_window(lua_State* L) {
    lua_getglobal(L, "bee");

    if (!lua_istable(L, -1)) {
        SDL_Log("Failed to find 'bee' table.");
        lua_close(L);
        return;
    }

    lua_newtable(L);

    luaL_Reg bee_window_funcs[] = {
        {"getSize", bee_window_getsize},
        {"getWidth", bee_window_getwidth},
        {"getHeight", bee_window_getheight},
        {"setSize", bee_window_setsize},
        {NULL, NULL}
    };

    luaL_setfuncs(L, bee_window_funcs, 0);

    lua_setfield(L, -2, "window");
}

void register_all(lua_State* L) {
    register_bee(L);
    register_bee_graphics(L);
    register_bee_window(L);
}
