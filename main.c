#include <stdio.h>
#include <stdbool.h>
#include "bee.h"
#undef main

const int DEFAULT_WINDOW_WIDTH = 800;
const int DEFAULT_WINDOW_HEIGHT = 600;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Color background_color = { 0, 0, 0, 255 };

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to initialize SDL; %s", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow(
        "title",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        DEFAULT_WINDOW_WIDTH,
        DEFAULT_WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        SDL_Log("Failed to create SDL window; %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        SDL_Log("Failed to create SDL renderer; %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    lua_State* L = luaL_newstate();

    if (!L) {
        SDL_Log("Failed to create Lua state.");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    luaL_openlibs(L);

    register_all(L);

    if (luaL_dofile(L, "main.lua") != LUA_OK) {
        SDL_Log("Failed to load script: %s\n", lua_tostring(L, -1));
        lua_close(L);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    bee_load(L);

    bool is_running = true;
    bool is_first_update = true;
    SDL_Event event;

    Uint64 FPS = 60;
    Uint64 last_tick_time = 0;

    while (is_running) {

        Uint64 frame_start_time = SDL_GetTicks64();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    is_running = false;
                    break;
                case SDL_KEYDOWN:
                    bee_keydown(L, &event);
                    break;
                case SDL_KEYUP:
                    bee_keyup(L, &event);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    bee_mousebuttondown(L, &event);
                    break;
                case SDL_MOUSEBUTTONUP:
                    bee_mousebuttonup(L, &event);
                    break;
                case SDL_MOUSEMOTION:
                    if (event.button.button == SDL_BUTTON_LEFT || 
                        event.button.button == SDL_BUTTON_RIGHT || 
                        event.button.button == SDL_BUTTON_MIDDLE) {
                        bee_mousebuttondown(L, &event);
                    }
                    bee_mousemove(L, &event);
                    break;
                default:
                    break;
            }
        }

        if (is_first_update) {
            last_tick_time = SDL_GetTicks64();
            is_first_update = false;
        }
        Uint64 current_tick_time = SDL_GetTicks64();
        double dt = (current_tick_time - last_tick_time) / 1000.0;
        bee_update(L, dt);
        last_tick_time = current_tick_time;

        SDL_SetRenderDrawColor(
            renderer, 
            background_color.r, 
            background_color.g, 
            background_color.b, 
            background_color.a
        );
        SDL_RenderClear(renderer);
        bee_draw(L);
        SDL_RenderPresent(renderer);

        Uint64 frame_end_time = SDL_GetTicks64();
        Uint64 frame_delta_time = frame_end_time - frame_start_time;
        if (frame_delta_time < 1000 / FPS) {
            SDL_Delay(1000 / FPS - frame_delta_time);
        }
        
    }

    lua_close(L);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}