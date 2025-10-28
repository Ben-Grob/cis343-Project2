#ifndef ZOOMJOYSTRONG_H
#define ZOOMJOYSTRONG_H

#include <SDL.h>   // ✅ Make sure this line stays like this — no SDL2/ prefix

// --- Window constants ---
#define WIDTH 800
#define HEIGHT 600

// --- Color structure ---
struct color {
    int r;
    int g;
    int b;
};

// --- Function prototypes ---
void setup();
void finish();
void set_color(int r, int g, int b);
void point(int x, int y);
void line(int x1, int y1, int x2, int y2);
void circle(int x, int y, int radius);
void rectangle(int x, int y, int w, int h);

#endif
