#include "core.h"
#include "input/input.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>

void processInput(GLFWwindow *window){                                          // handle inputs (may be set callback)
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){                      // escape key is pressed
        glfwSetWindowShouldClose(window, true);
        log("Esc key pressed: closing window");
    }
}