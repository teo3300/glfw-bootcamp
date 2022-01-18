#include "framebuffer_size/framebuffer_size.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);                                            // dinamically adjust viewport to Wsize
}