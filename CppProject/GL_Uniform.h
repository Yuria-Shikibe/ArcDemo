﻿#pragma once
#include <glad/glad.h>

#include "Color.h"
#include "Matrix3D.h"

namespace Graphic{
	inline void uniformColor(const GLint location, const Color& color){
		glUniform4f(location, color.r, color.g, color.b, color.a);
	}

	inline void uniformTexture(const GLint location, const GLint& texSlot) {
		glUniform1i(location, texSlot);
	}

	inline void uniform1i(const GLint location, const GLint& unit){
		glUniform1i(location, unit);
	}

	inline void uniformMat3D(const GLint location, const Geom::Matrix3D& mat){
		glUniformMatrix3fv(location, 1, GL_FALSE, mat.getVal());
	}
}
