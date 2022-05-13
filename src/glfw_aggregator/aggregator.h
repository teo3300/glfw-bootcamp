#pragma once

void glfwRequired(int versionMajor, int versionMinor, int profile);

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
    #define glDebugMaxVertexAttribs()\
    {\
    int nrAttributes;\
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);\
    debug("Maximum # of vertex attributes supported: %d", nrAttributes);\
    }
#else
    #define glDebugMaxVertexAttribs() 
#endif