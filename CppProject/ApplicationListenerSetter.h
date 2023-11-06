#pragma once
#include <iostream>


#include "OS.h"
#include "Renderer.h"
#include <GLFW/glfw3.h>

#include "Core.h"


static void throw_GL_Exception(const int error_code, const char* description) {
    std::cout << "ERROR CODE: " << error_code << std::endl << description << std::endl;
}

static void framebufferSizeCallback(GLFWwindow* window, const int width, const int height) {
    // make sure the viewport matches the new windowMain dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.

    glViewport(0, 0, width, height);
    Graphic::getRenderer().resize(width, height);
    // OS::width = width;
    // OS::height = height;
    //
    // std::cout << OS::width << " | " << OS::height << std::endl;
}

static void cursorPosCallBack(GLFWwindow* window, const double xPos, const double yPos) {
    Core::input->setPos(static_cast<float>(xPos), static_cast<float>(yPos));
}

static void dropCallBack(GLFWwindow* window, int path_count, const char* paths[]) {
    

}

static void cursorEntered(GLFWwindow* window, const int entered) {
    Core::input->setInbound(entered);
}

static void charCallBack(GLFWwindow* window, unsigned int codepoint) {
    

}

static void charModCallBack(GLFWwindow* window, unsigned int codepoint, int mods) {
    

}

static void scrollCallBack(GLFWwindow* window, const double xOffset, const double yOffset){
    Core::input->setScrollOffset(static_cast<float>(xOffset), static_cast<float>(yOffset));
}

static void scaleCallBack(GLFWwindow* window, float xScale, float yScale){
	
}

inline void loadListeners(GLFWwindow* window) {
    glfwSetErrorCallback(throw_GL_Exception);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, cursorPosCallBack);
    glfwSetDropCallback(window, dropCallBack);
    glfwSetCursorEnterCallback(window, cursorEntered);
    glfwSetCharCallback(window, charCallBack);
    glfwSetCharModsCallback(window, charModCallBack);
    glfwSetScrollCallback(window, scrollCallBack);
    glfwSetWindowContentScaleCallback(window, scaleCallBack);

}
