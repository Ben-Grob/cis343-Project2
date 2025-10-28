#include "zoomjoystrong.h"
#include <math.h>
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct color current;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

void setup() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("ZoomJoyString",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WIDTH, HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
    if (!texture) {
        fprintf(stderr, "SDL_CreateTexture Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
}

void set_color(int r, int g, int b) {
    current.r = r;
    current.g = g;
    current.b = b;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

void point(int x, int y) {
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderDrawPoint(renderer, x, y);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void line(int x1, int y1, int x2, int y2) {
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void circle(int x, int y, int r) {
    for (float i = 0; i < 2 * M_PI; i += 0.01) {
        int px = x + r * cos(i);
        int py = y + r * sin(i);
        point(px, py);
    }
}

void rectangle(int x, int y, int w, int h) {
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void wait_for_exit() {
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = 1;
        }
        SDL_Delay(10);
    }
}

void finish() {
    wait_for_exit(); // Wait for user to close window
    if (texture) SDL_DestroyTexture(texture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}
