#ifndef CUSTOMSHADERMANAGER_H
#define CUSTOMSHADERMANAGER_H

#include "GL/glew.h"
#include <QtOpenGL/qgl.h>
#include <vector>

class CustomShaderManager
{
public:
    CustomShaderManager();
    ~CustomShaderManager();

    GLuint getProgramId();
    void selectShader(int);

private:
    GLuint vertexShaderID;
    GLuint geometryShaderID;
    GLuint fragmentShaderID;
    GLuint programID;

    unsigned int selectedShaders;

    std::vector<char *> sourceVertexShaders;
    std::vector<char *> sourceFragmentShaders;
    std::vector<char *> sourceGeometryShaders;
};

#endif // CUSTOMSHADERMANAGER_H
