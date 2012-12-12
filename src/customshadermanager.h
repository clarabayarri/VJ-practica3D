#ifndef CUSTOMSHADERMANAGER_H
#define CUSTOMSHADERMANAGER_H

#include "Globals.h"
#include <vector>
#include "Constants.h"

#define SHADER_VERT_EXT	".vert"
#define SHADER_FRAG_EXT	".frag"

class CustomShaderManager
{
public:
    CustomShaderManager();
    ~CustomShaderManager();

	void initShaders();

    void selectShader(int);

private:
	std::vector<GLuint> programIDs;

    unsigned int selectedShaders;

	void compileShader(std::string sourceFile);
};

#endif // CUSTOMSHADERMANAGER_H
