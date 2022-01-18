#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core.h"
#include "data.h"
#include "shaders.h"
#include "input/input.h"
#include "framebuffer_size/framebuffer_size.h"

int main(){

    GLFWwindow* window;

    //  initializing GLFW
    if(!glfwInit()){                                                            // well... init
        log_error("Failed to initialize GLFW");
        return -1;
    }
    glfwRequired(4, 3, GLFW_OPENGL_CORE_PROFILE);

    //  creating window
    window = glfwCreateWindow(800, 600, "OpenGL test", NULL, NULL);             // new window
    if (!window){                                                               // exit with error if window init failed
        log_error("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);                                             // OpenGL context on current window
    log_log("Window successfully created");

    //  initializing GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){                   // try loading GL functions
        log_error("Failed to initialize GLAD");
        return -1;
    }
    log_log("GLAD successfully initialized");

    //  setting GL viewport
    glViewport(0, 0, 800, 600);                                                 // setting initial GL viewport
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);          // dinamically adjust GL viewport

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);                                       // set default clear color

    glGenVertexArrays(1, &VAO);                                                 // generate array buffer
    glGenBuffers(1, &VBO);                                                      // generate new buffer (return addr)

    glBindVertexArray(VAO);                                                     // bind Vertex Array
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                         // bind buffer for Vertex Objects
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), vertices, GL_STATIC_DRAW);   // copy data to buffer

    glVertexAttribPointer(                                                      // 
        0,                                                                      // VA to configure (location = 0 in shader)
        3,                                                                      // size of VA (vec3)
        GL_FLOAT,                                                               // VA type is vec* (floats)
        GL_FALSE,                                                               // normalize data
        3*sizeof(float),                                                        // offset between vertex (0 to autodetect)
        (void*)0);                                                              // offset of data begin
    glEnableVertexAttribArray(0);                                               // set to use vertexAttrib 0

    unsigned int shaderProgram =
        shaderCompileProgram("shaders/main.vert", "shaders/main.frag");

    glUseProgram(shaderProgram);                                                // set shader to use

    //  main loop
    while(!glfwWindowShouldClose(window)){  
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);                                           // clear buffer (to avoid ghosting)
        glDrawArrays(GL_TRIANGLES, 0, 3);                                       // draw triangle on buffer
        
        glfwPollEvents();                                                       // input poll
        glfwSwapBuffers(window);                                                // double framebuffer
    }
    glfwTerminate();                                                            // free resources

    log_log("Execution ended");
    return 0;
}