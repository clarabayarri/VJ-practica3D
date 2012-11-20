#include "customshadermanager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <QFileDialog>
using namespace std;

#define glError() { \
    GLenum err = glGetError(); \
    while (err != GL_NO_ERROR) { \
        printf("glError: %s caught at %s:%u\n", (char *)gluErrorString(err), __FILE__, __LINE__); \
        err = glGetError(); \
    } \
}

CustomShaderManager::CustomShaderManager(): vertexShaderID(0),
    geometryShaderID(0), fragmentShaderID(0), programID(0), selectedShaders(0)
{
	// Init existing shaders according to defined constants
	// Atention: make sure you add them in the same order as constants!!
    addShaderSource("nomShader1");
}

void addShaderSource(char* sourceFile)
{
	char *vertex = (char *)"shaders/"+ sourceFile +".vert";
	sourceVertexShaders.push_back(vertex);
	char *fragment = (char *)"shaders/"+ sourceFile +".frag";
	sourceFragmentShaders.push_back(fragment);
}

CustomShaderManager::~CustomShaderManager()
{
    glDeleteShader(vertexShaderID);
    glDeleteShader(geometryShaderID);
    glDeleteShader(fragmentShaderID);
    glDeleteProgram(programID);
}

void printShaderInfoLog(GLint shader) {
    int infoLogLen = 0;
    int charsWritten = 0;
    GLchar *infoLog;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
    if (infoLogLen > 0) {
        infoLog = new GLchar[infoLogLen];
        // error check for fail to allocate memory omitted
        glGetShaderInfoLog(shader, infoLogLen, &charsWritten, infoLog);
        cout << "InfoLog : " << endl << infoLog << endl;
        delete [] infoLog;
    }
}

GLuint CustomShaderManager::getProgramId()
{
    return programID;
}

void readFile(const char* filename, string& shaderSource) {
    ifstream infile(filename);

    if(!infile) {
        //error
        cout << "error" << endl;
    }

    stringstream stream;
    stream << infile.rdbuf();
    infile.close();

    shaderSource = stream.str();
}

void CustomShaderManager::selectShader(int selection)
{
    selectedShaders = (unsigned int)selection;
    if(programID != 0) {
        glDeleteShader(vertexShaderID);
        glDeleteShader(geometryShaderID);
        glDeleteShader(fragmentShaderID);
        glDeleteProgram(programID);
    }
    if(selection == 0) programID = 0;
    else {
        GLint compiled = 0;

        string shader;
        char *inputFile = sourceVertexShaders[selection];
        readFile(inputFile, shader);
        const char* shader2 = shader.c_str();
        vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderID,1,(const GLchar **)&shader2,0);
        glCompileShader(vertexShaderID);
        glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &compiled);
        if(compiled==0) {
            cout << "Vertex shader not compiled." << endl;
            printShaderInfoLog(vertexShaderID);
        }

        string shader3;
        char *inputFile2 = sourceFragmentShaders[selection];
        readFile(inputFile2, shader3);
        const char* shader4 = shader3.c_str();
        fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderID,1,(const GLchar **)&shader4,0);
        glCompileShader(fragmentShaderID);
        glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &compiled);
        if(compiled==0) {
            cout << "Fragment shader not compiled." << endl;
            printShaderInfoLog(fragmentShaderID);
        }

        programID = glCreateProgram();
        glAttachShader(programID,vertexShaderID);
		glError()

		// Donc per suposat que no tindrem Geometry shaders
        /*if(selection == 5) { //geometry shader
            string shader4;
            char *inputFile = sourceGeometryShaders[0];
            readFile(inputFile, shader4);
            const char* shader5 = shader4.c_str();
            geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER_EXT);
            glShaderSource(geometryShaderID,1,(const GLchar **)&shader5,0);
            glCompileShader(geometryShaderID);
            glGetShaderiv(geometryShaderID, GL_COMPILE_STATUS, &compiled);
            if(compiled==0) {
                cout << "Geometry shader not compiled." << endl;
                printShaderInfoLog(geometryShaderID);
            }
            glAttachShader(programID,geometryShaderID);
			glError()
            GLint maxVertices;
            glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT, &maxVertices);
			glError()
            glProgramParameteriEXT(programID, GL_GEOMETRY_INPUT_TYPE, GL_TRIANGLES);
            glProgramParameteriEXT(programID, GL_GEOMETRY_OUTPUT_TYPE, GL_TRIANGLE_STRIP);
            glProgramParameteriEXT(programID, GL_GEOMETRY_VERTICES_OUT, maxVertices);
            glError()
        }*/

        glAttachShader(programID,fragmentShaderID);

        if(selection == 4) {
            //demanar textura a fer servir pel sphere mapping
            QString fileName = QFileDialog::getOpenFileName(NULL, "Open image File", "", "Models (*.jpg)");
            if (fileName.length()) {
                glEnable(GL_TEXTURE_2D);
                QImage image(fileName);
                QImage data = QGLWidget::convertToGLFormat(image);

                GLuint texturaID;
                glGenTextures(1, &texturaID);
                glBindTexture(GL_TEXTURE_2D, texturaID);
                glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,data.width(),data.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,data.bits());
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            }
        }

        glLinkProgram(programID);

        GLint IsLinked;
        glGetProgramiv(programID, GL_LINK_STATUS, (GLint *)&IsLinked);
        if(IsLinked==0) {
            cout << "Failed to link shader." << endl;
            GLint maxLength;
            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
            if(maxLength>0) {
                    char *pLinkInfoLog = new char[maxLength];
                    glGetProgramInfoLog(programID, maxLength, &maxLength, pLinkInfoLog);
                    cout << pLinkInfoLog << endl;
                    delete [] pLinkInfoLog;
            }
        }
    }

}


