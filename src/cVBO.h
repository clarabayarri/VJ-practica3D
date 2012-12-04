#pragma once
#include "Globals.h"
#include "modelElements.h"
#include <vector>

class cVBO
{
public:
	cVBO(void);
	~cVBO(void);

	void GenerateVerticesArray	(const GLfloat vertices[], int size);
	void GenerateNormalsArray	(const GLfloat normals[], int size);
	void GenerateFacesArray		(const GLuint faces[], int size);
	void GenerateTextureArray	(const GLfloat textures[], int size);

	virtual void Render();

protected:
	std::vector<vertex> vertices;
    std::vector<face> faces;
	std::vector<std::pair<float,float> > textures;
    
	void GenerateArrays();
	void GenerateTextureArray();

private:
	GLuint * verticesId;
	GLuint * normalsId;
	GLuint * facesId;
	GLuint * happy;
	GLuint * texturesId;
	
	int triangleCount;

	bool verticesReady;
	bool normalsReady;
	bool facesReady;
	bool texturesReady;
};

