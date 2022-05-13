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
    debug("loading %s ...", shader_file);

    int shader;

    // returns 0 if fails

    shader = glCreateShader(shader_type);                                       // create new shader

    FILE* fptr = fopen(shader_file, "rb");                                      // open shader file
    lib_requires(fptr,
        "Could not open shader file \"%s\"", shader_file);

    fseek(fptr, 0, SEEK_END);
    long fsize = ftell(fptr);                                                   // get file length
    fseek(fptr, 0, SEEK_SET);

    char* source_buffer = (char*)malloc(fsize+1);                               // prepare buffer
    *(source_buffer+fsize) = '\0';                                              // only place null_char at end of line
    lib_requires(source_buffer,
        "Could not reserve memory to compile '%s'", shader_file);

    requires(fsize == fread(source_buffer, 1, fsize, fptr),                     // read file
        "Could not read shader file '%s'", shader_file);

    glShaderSource(shader, 1, (const GLchar**)  &source_buffer, NULL);          // load source
    glCompileShader(shader);

    free(source_buffer);                                                        // release memory

    lib_requires(shaderCompilationSuccess(shader),                                  // output errors
        "%s\twhile compiling %s", compilation_log, shader_file);
    log("'%s' compiled", shader_file);
    return shader;
}