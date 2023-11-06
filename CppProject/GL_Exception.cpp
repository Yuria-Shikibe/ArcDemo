#include "GL_Exception.h"
GL_Exception::GL_Exception() = default;

GL_Exception::GL_Exception(char const* message): exception(message){
}

GL_Exception::GL_Exception(char const* message, const int i): exception(message, i){
}

GL_Exception::GL_Exception(exception const& other): exception(other){
}
