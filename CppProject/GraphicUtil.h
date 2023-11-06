#pragma once
#include "Shader.h"

namespace Graphic{
	namespace Shaders{
		inline Shader* texPost;
	}

	inline void loadInbuiltAsserts() {
		Shaders::texPost = new Shader{ "tex-std" };

		Shaders::texPost->setUniformer([](const Shader& shader) {

		});
	}

	inline void disposeInbuiltAsserts() {
		delete Shaders::texPost;
	}
}
