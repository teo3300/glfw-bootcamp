#include "shaders.h"
#include "core.h"
#include <glad/glad.h>

extern char compilation_log[INFO_LOG_BUFF_SIZE];

int shaderProgramLink(unsigned int program){
    log_debug("compiling program");
    glLinkProgram(program);    
    int success;

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(program, INFO_LOG_BUFF_SIZE, NULL, compilation_log);
        log_error(compilation_log);
        return 0;
    }
    log_debug("shader program successfully linked");
    return program;
}

unsigned int shaderCompileProgramFull(char* vertexPath, char* fragmentPath, char* geometryPath){

    requires(vertexPath || fragmentPath || geometryPath,
        "Provide at least one shader for program");

    unsigned int shaderProgram = 0;
    unsigned int vertexShader = 0,
        fragmentShader = 0,
        geometryShader = 0;

    requires(shaderProgram = glCreateProgram(),
        "Could not create shader program");

    if(vertexPath){
        requires(vertexShader = shaderLoadAndCompile(vertexPath, GL_VERTEX_SHADER),
            vertexPath);
        glAttachShader(shaderProgram, vertexShader);
    }
    if(fragmentPath){
        requires(fragmentShader = shaderLoadAndCompile(fragmentPath, GL_FRAGMENT_SHADER),
            fragmentPath);
        glAttachShader(shaderProgram, fragmentShader);
    }
    if(geometryPath){
        requires(geometryShader = shaderLoadAndCompile(geometryPath, GL_GEOMETRY_SHADER),
            geometryPath);
        glAttachShader(shaderProgram, geometryShader);
    }

    requires(shaderProgramLink(shaderProgram),
        "Could not link shader programs");

    if(vertexShader)glDeleteShader(vertexShader);
    if(fragmentShader)glDeleteShader(fragmentShader);
    if(geometryPath)glDeleteShader(geometryShader);

    return shaderProgram;
}