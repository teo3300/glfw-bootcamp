#include "shaders.h"
#include <glad/glad.h>
#include <stdlib.h>
#include "core.h"

extern char compilation_log[INFO_LOG_BUFF_SIZE];

static inline int shaderCompilationSuccess(GLuint shader){
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(success) return 1;
    glGetShaderInfoLog(shader, INFO_LOG_BUFF_SIZE, NULL, compilation_log);
    return 0;
}

int shaderLoadAndCompile(char* shader_file, GLenum shader_type){
    log_debug(shader_file);

    int shader;

    // returns 0 if fails

    shader = glCreateShader(shader_type);                                       // create new shader

    FILE* fptr = fopen(shader_file, "rb");                                      // open shader file
    requires(fptr,
        "Could not load shader file");

    fseek(fptr, 0, SEEK_END);
    long fsize = ftell(fptr);                                                   // get file length
    fseek(fptr, 0, SEEK_SET);

    char* source_buffer = (char*)malloc(fsize+1);                               // prepare buffer
    *(source_buffer+fsize) = '\0';                                              // only place null_char at end of line
    requires(source_buffer,
        "Could not reserve memory for shader compilation");

    requires(fsize == fread(source_buffer, 1, fsize, fptr),                     // read file
        "Could not read shader file");

    glShaderSource(shader, 1, (const GLchar**)  &source_buffer, NULL);          // load source
    glCompileShader(shader);

    free(source_buffer);                                                        // release memory

    requires(shaderCompilationSuccess(shader),                                  // output errors
        compilation_log);
    log_debug("shader successfully loaded");
    return shader;
}