#include "cVBO.h"

cVBO::cVBO(void):verticesId(new GLuint[1]),normalsId(new GLuint[1]),facesId(new GLuint[1]),texturesId(new GLuint[1]),
				verticesReady(false),normalsReady(false),facesReady(false),texturesReady(false){}

cVBO::~cVBO(void){
	if(verticesReady)	glDeleteBuffers(1,verticesId);
	if(normalsReady)	glDeleteBuffers(1,normalsId);
	if(facesReady)		glDeleteBuffers(1,facesId);
	if(texturesReady)	glDeleteBuffers(1,texturesId);
}

void cVBO::GenerateVerticesArray(const GLfloat vertices[], int size) {
	glGenBuffers(1,verticesId);
	glBindBuffer(GL_ARRAY_BUFFER,*verticesId);
    glBufferData(GL_ARRAY_BUFFER,3*size*sizeof(float),vertices,GL_STATIC_DRAW);
	verticesReady=true;
}

void cVBO::GenerateNormalsArray(const GLfloat normals[], int size) {
	glGenBuffers(1,normalsId);
	glBindBuffer(GL_ARRAY_BUFFER,*normalsId);
    glBufferData(GL_ARRAY_BUFFER,3*size*sizeof(float),normals,GL_STATIC_DRAW);
	normalsReady=true;   
}

void cVBO::GenerateFacesArray(const GLuint faces[], int size){
	glGenBuffers(1,facesId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,*facesId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,3*size*sizeof(unsigned int),faces,GL_STATIC_DRAW);
	triangleCount = size;
	facesReady = true;
}

void cVBO::GenerateTextureArray(const GLfloat textures[], int size) {
	glGenBuffers(1,texturesId);
	glBindBuffer(GL_ARRAY_BUFFER,*texturesId);
    glBufferData(GL_ARRAY_BUFFER,2*size*sizeof(float),textures,GL_STATIC_DRAW);
	texturesReady = true;
}

void cVBO::Render() {
	if (verticesReady && facesReady) {
		glBindBuffer(GL_ARRAY_BUFFER, *verticesId);
		glVertexPointer(3,GL_FLOAT,0,(GLvoid *)0);
		glEnableClientState(GL_VERTEX_ARRAY);

		if (normalsReady) {
			glBindBuffer(GL_ARRAY_BUFFER, *normalsId);
			glNormalPointer(GL_FLOAT,0,(GLvoid *)0);
			glEnableClientState(GL_NORMAL_ARRAY);
		}

		if (texturesReady) {
			glBindBuffer(GL_ARRAY_BUFFER, *texturesId);
			glTexCoordPointer(2,GL_FLOAT,0,(GLvoid *)0);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,*facesId);
		glDrawElements(GL_TRIANGLES,triangleCount*3,GL_UNSIGNED_INT,(GLvoid *)0);

		glDisableClientState(GL_VERTEX_ARRAY);
		if(normalsReady) glDisableClientState(GL_NORMAL_ARRAY);
		if(texturesReady) glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER,0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	}
}

void cVBO::GenerateArrays() {

    GLfloat * verticesArray = new GLfloat[vertices.size()*3];
    for (unsigned int i = 0; i < vertices.size(); ++i) {
        verticesArray[i*3]   = vertices[i].coord[0];
        verticesArray[i*3+1] = vertices[i].coord[1];
        verticesArray[i*3+2] = vertices[i].coord[2];
	}

	GLfloat * normalsArray = new GLfloat[vertices.size()*3];
	for (unsigned int i = 0; i < vertices.size(); ++i) {
        normalsArray[i*3]   = vertices[i].normal[0];
        normalsArray[i*3+1] = vertices[i].normal[1];
        normalsArray[i*3+2] = vertices[i].normal[2];
    }

	GLuint * indexs = new GLuint[faces.size()*3];
    for(unsigned int i=0; i<faces.size(); i++)
        for(int j=0; j < 3; j++)
            indexs[i*3+j] = faces[i].vertices[j];

	GenerateVerticesArray(verticesArray,vertices.size());
	GenerateNormalsArray(normalsArray,vertices.size());
	GenerateFacesArray(indexs,faces.size());
}

void cVBO::GenerateTextureArray() {
	GLfloat * textureArray = new GLfloat[textures.size()*2];
    for(unsigned int i=0; i< textures.size(); i++) {
		textureArray[i*2] = textures[i].first;
		textureArray[i*2+1] = textures[i].second;
	}
	GenerateTextureArray(textureArray,textures.size());
}