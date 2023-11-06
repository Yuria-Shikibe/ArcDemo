// ReSharper disable CppDeclaratorNeverUsed
#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GL_Exception.h"
#include "OS.h"
#include "Renderer.h"

namespace Graphic{
	inline static const std::string ASSERTS_DIR = "D:\\projects\\study_cpp_porj\\Build\\asserts\\";

    static std::string getPath(const std::string& name){
        return ASSERTS_DIR + name;
    }

    static void enableMSAA(const unsigned int scale = 2){
        glfwWindowHint(GLFW_SAMPLES, scale);
    }

	static GLFWwindow* windowMain = nullptr;

    // ReSharper disable once CppInconsistentNaming
    static void initGLFW(){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    }

	inline GLFWwindow& getWindow(){
        return *windowMain;
    }

	inline bool initialized(){
        return windowMain != nullptr;
    }
    /**
     *  glfw: whenever the windowMain size changed (by OS or user resize) this callback function executes
     */

    static void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)glfwSetWindowShouldClose(window, true);
    }

    static GLint sizeofType(const GLenum type){
	    switch(type){
	        case GL_FLOAT: return 4;
	        case GL_UNSIGNED_INT: return 4;
	        case GL_INT: return 4;
	        case GL_UNSIGNED_BYTE: return 1;
	        case GL_BYTE: return 1;
			default: throw GL_Exception{ "Unregistered Type!" };
	    }
    }

    static GLFWwindow* initWindow(const std::string& windowTitle, const int scr_width = 800, const int scr_height = 800, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr) noexcept(false) {
        // glfw windowMain creation
        windowMain = glfwCreateWindow(scr_width, scr_height, windowTitle.c_str(), monitor, share);
        // renderer = new Renderer();
        if (windowMain == nullptr)
        {
            glfwTerminate();
            throw GL_Exception("Failed to create GLFW windowMain");
        }

        glfwMakeContextCurrent(windowMain);
        // glfwSetFramebufferSizeCallback(windowMain, framebufferSizeCallback);
        // glfwSetInputMode(windowMain, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            throw GL_Exception("Failed to create GLFW windowMain");
        }

        glfwSwapInterval(1);

        initRenderer(scr_width, scr_height);

        return windowMain;
	}
}
