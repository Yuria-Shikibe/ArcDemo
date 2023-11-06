#pragma once
#include <exception>

// ReSharper disable once CppInconsistentNaming
class GL_Exception final : public std::exception{
public:
	GL_Exception();

	explicit GL_Exception(char const* message);

	GL_Exception(char const* message, const int i);

	explicit GL_Exception(exception const& other);
};

