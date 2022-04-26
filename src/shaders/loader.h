#pragma once

#include <glad/glad.h>

#define INFO_LOG_BUFF_SIZE  512

int shaderLoadAndCompile(char* shader_file, GLenum shader_type);