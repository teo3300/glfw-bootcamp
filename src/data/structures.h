#pragma once

#define f_t float
#define c_t unsigned char

typedef struct{
    f_t x;
} vec1;

typedef struct{
    f_t x,
        y;
} vec2;

typedef struct{
    f_t x,
        y,
        z;
} vec3;

typedef struct{
    f_t x,
        y,
        z,
        w;
} vec4;

typedef struct{
    c_t r,
        g,
        b;
} color;

typedef struct{
    c_t r,
        g,
        b,
        a;
} alpha_color;