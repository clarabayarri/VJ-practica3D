#include "customshadermanager.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


CustomShaderManager::CustomShaderManager(): selectedShaders(-1)
{
	
}

CustomShaderManager::~CustomShaderManager()
{
    
}

void CustomShaderManager::initShaders() 
{
	// Init existing shaders according to defined constants
	// Atention: make sure you add them in the same order as constants!!
    compileShader("crt_display");
	compileShader("height");
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

void readFile(std::string filename, string& shaderSource) {
    ifstream infile(filename);
	bool good = infile.good();
    if(!infile) {
        //error
        cout << "error" << endl;
    }

    stringstream stream;
    stream << infile.rdbuf();
    infile.close();

    shaderSource = stream.str();
}

void glError() { 
    GLenum err = glGetError(); 
    while (err != GL_NO_ERROR) { 
        printf("glError: %s caught at %s:%u\n", (char *)gluErrorString(err), __FILE__, __LINE__); 
        err = glGetError(); 
    }
}

void CustomShaderManager::compileShader(std::string sourceFile)
{
	GLint compiled = 0;
	std::string vertex = ("shaders\\" + sourceFile + SHADER_VERT_EXT);
	std::string fragment = ("shaders\\" + sourceFile + SHADER_FRAG_EXT);

    string shader;
    readFile(vertex, shader);
    const char* shader2 = shader.c_str();

    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID,1,(const GLchar **)&shader2,0);
    glCompileShader(vertexShaderID);
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &compiled);
    if(compiled==0) {
        cout << "Vertex shader not compiled." << endl;
        printShaderInfoLog(vertexShaderID);
    }

    string shader3;
    readFile(fragment, shader3);
    const char* shader4 = shader3.c_str();
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID,1,(const GLchar **)&shader4,0);
    glCompileShader(fragmentShaderID);
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &compiled);
    if(compiled==0) {
        cout << "Fragment shader not compiled." << endl;
        printShaderInfoLog(fragmentShaderID);
    }

	GLuint programID = glCreateProgram();

	glAttachShader(programID,vertexShaderID);
	glError();
    glAttachShader(programID,fragmentShaderID);
	glError();
    glLinkProgram(programID);
	glError();
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
	programIDs.push_back(programID);
}

void CustomShaderManager::selectShader(int selection)
{
	selectedShaders = (unsigned int)selection;
    if(selection == -1) glUseProgram(0);
    else glUseProgram(programIDs[selection]);
}


