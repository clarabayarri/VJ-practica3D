#ifndef CUSTOMSHADERMANAGER_H
#define CUSTOMSHADERMANAGER_H

#include "Globals.h"
#include <vector>

class CustomShaderManager
{
public:
    CustomShaderManager();
    ~CustomShaderManager();

    GLuint getProgramId();
    void selectShader(int);

private:
    std::vector<GLuint> vertexShaderIDs;
    std::vector<GLuint> fragmentShaderIDs;
    GLuint programID;

    unsigned int selectedShaders;

	void compileShader(std::string sourceFile);
};

#endif // CUSTOMSHADERMANAGER_H
