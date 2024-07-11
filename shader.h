#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
private:


public:
	Shader(const char* vertexPath, const char* fragmentPath); // input strings referencing filenames to have as input for shaders
	unsigned int ID = 0; // references ID for shaderprogram

	void use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
};

#endif