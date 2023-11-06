#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GL_Exception.h"
#include <fstream>
#include <iostream>


std::string Shader::readFile(const std::string& name, const std::string& path){
	if (std::ifstream file_stream(path + name); file_stream.is_open()) {
		std::stringstream file_contents;
		std::string line;

		while (std::getline(file_stream, line)) {
			file_contents << line << "\n";
		}

		file_stream.close();
		return file_contents.str();
	}
	else {
		throw GL_Exception(std::string("Unable to Read File: " + path + name).data());
	}
}

std::string Shader::shaderTypeStr(const unsigned shaderType){
	switch(shaderType){
	case GL_VERTEX_SHADER: return "Vertex";
	case GL_FRAGMENT_SHADER: return "FRAGMENT";
	default: return "UNDEFINED SHADER";
	}
}

template <size_t size>
unsigned Shader::attachShaders(const unsigned int(&shaders)[size]){
	int success;
	// link shaders
	const unsigned int shaderProgram = glCreateProgram();

	for(size_t i = 0; i < size; ++i){
		glAttachShader(shaderProgram, shaders[i]);
	}
		
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		constexpr unsigned int exceptionLength = 1024;
		char infoLog[exceptionLength];
		glGetProgramInfoLog(shaderProgram, exceptionLength, nullptr, infoLog);
		throw GL_Exception(("ERROR::SHADER::PROGRAM::LINKING_FAILED\n" + std::string(infoLog)).data());
	}

	return shaderProgram;
}

unsigned Shader::compile(const std::string& src, const unsigned shaderType){
	const unsigned int shader = glCreateShader(shaderType);
	const char* vert = src.c_str();

	glShaderSource(shader, 1, &vert, nullptr);
	glCompileShader(shader);
	// check for shader compile errors
	int success;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		constexpr unsigned int exceptionLength = 1024;
		char infoLog[exceptionLength];
		glGetShaderInfoLog(shader, exceptionLength, nullptr, infoLog);
		throw GL_Exception(("ERROR::SHADER::" + shaderTypeStr(shaderType) + "::COMPILATION_FAILED\n" + std::string(infoLog)).data());
	}

	return shader;
}

Shader::Shader(const std::string& vertName, const std::string& fragName){
	const unsigned int vertexShader = compile(readFile(vertName + ".vert"), GL_VERTEX_SHADER);
	const unsigned int fragmentShader = compile(readFile(vertName + ".frag"), GL_FRAGMENT_SHADER);

	const unsigned int shaders[] = { vertexShader, fragmentShader };
	shaderRef = attachShaders(shaders);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
}

Shader::Shader(const std::string& name): Shader(name, name){
        
}

Shader::~Shader(){
	glDeleteProgram(get());
}

Shader::SHADER_INDEX Shader::operator*() const{
	return get();
}

void Shader::apply() const{
	drawer(*this);
}

Shader::SHADER_INDEX Shader::get() const{
	return shaderRef;
}


