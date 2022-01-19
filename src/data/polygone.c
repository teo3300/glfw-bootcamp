#include "data/polygone.h"

const float polygone_vertices[] = {
    0.5f,  0.5f, 0.0f, // top right
    0.5f, -0.5f, 0.0f, // bottom right
   -0.5f, -0.5f, 0.0f, // bottom left
   -0.5f,  0.5f, 0.0f // top left
};
unsigned int polygone_indices[] = { // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3 // second triangle
};