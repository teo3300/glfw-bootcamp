#pragma once

int shaderLink(unsigned int program);

#define shaderCompileProgram(vertexPath, fragmentPath)\
    shaderCompileProgramFull(vertexPath, NULL, fragmentPath)

unsigned int shaderCompileProgramFull(char* vertexPath, char* geometryPath, char* fragmentPath);