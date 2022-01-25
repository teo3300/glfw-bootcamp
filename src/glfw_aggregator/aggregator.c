#include <GLFW/glfw3.h>

#include "glfw_aggregator/aggregator.h"

void glfwRequired(int versionMajor, int versionMinor, int profile){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);                   // minimum OpenGL version required
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, profile);                               // just require core
}
