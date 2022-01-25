#include "core/random.h"

#include <math.h>
#include <time.h>

float glfwRand(){
    return (sin((double)clock()) / 2.0f + 0.5f);
}

float glfwRandInterval(float min, float max){
    return (glfwRand() * (max - min) + min);
}

int glfwRrandInt(int min, int max){
    return floor(glfwRandInterval(min, max));
}