#pragma once

int shaderLink(unsigned int program);

#define shaderCompileProgram(vertexPath, fragmentPath)\
    shaderCompileProgramFull(vertexPath, fragmentPath, (void*)NULL)

unsigned int shaderCompileProgramFull(char* vertexPath, char* fragmentPath, char* geometryPath);