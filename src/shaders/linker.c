#include "shaders.h"
#include "core.h"
#include <glad/glad.h>

extern char compilation_log[INFO_LOG_BUFF_SIZE];

int shaderProgramLink(unsigned int program){
    debug("compiling...");
    glLinkProgram(program);    
    int success;

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(program, INFO_LOG_BUFF_SIZE, NULL, compilation_log);
        error("%s\tError linking programs", compilation_log);
        return 0;
    }
    debug("compilation successful");
    return program;
}

unsigned int shaderCompileProgramFull(char* vertexPath, char* geometryPath, char* fragmentPath){

    lib_requires(vertexPath || fragmentPath || geometryPath,
        "Provide at least one shader for program");

    unsigned int shaderProgram = 0;
    unsigned int vertexShader = 0,
        fragmentShader = 0,
        geometryShader = 0;

    lib_requires(shaderProgram = glCreateProgram(), 
        "Could not create shader program");

    if(vertexPath){
        lib_requires(vertexShader = shaderLoadAndCompile(vertexPath, GL_VERTEX_SHADER),
            "failed to compile vertex shader '%s'", vertexPath);
        glAttachShader(shaderProgram, vertexShader);
    }else debug("missing vertex shader");
    if(fragmentPath){
        lib_requires(fragmentShader = shaderLoadAndCompile(fragmentPath, GL_FRAGMENT_SHADER),
            "failed to compile fragment shader '%s'", fragmentPath);
        glAttachShader(shaderProgram, fragmentShader);
    }else debug("missing fragment shader");
    if(geometryPath){
        lib_requires(geometryShader = shaderLoadAndCompile(geometryPath, GL_GEOMETRY_SHADER),
            "failed to compile geometry shader '%s'", geometryPath);
        glAttachShader(shaderProgram, geometryShader);
    }else debug("missing geometry shader");

    lib_requires(shaderProgramLink(shaderProgram),
        "Could not link shader programs");

    if(vertexShader)glDeleteShader(vertexShader);
    if(fragmentShader)glDeleteShader(fragmentShader);
    if(geometryPath)glDeleteShader(geometryShader);

    return shaderProgram;
}