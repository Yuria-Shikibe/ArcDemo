#pragma once
#include "Texture2D.h"

namespace Graphic{
	class TextureRegion
	{
	public:
		Texture2D* data = nullptr;
		float u0 = 0.0f, v0 = 0.0f, u1 = 1.0f, v1 = 1.0f;

		explicit TextureRegion(Texture2D* data)
			: data(data){
		}

		TextureRegion(Texture2D* data, const float u0, const float v0, const float u1, const float v1)
			: data(data),
			  u0(u0),
			  v0(v0),
			  u1(u1),
			  v1(v1){
		}

		void resize(const float _u0, const float _v0, const float _u1, const float _v1) {
			u0 = _u0;
			v0 = _v0;
			u1 = _u1;
			v1 = _v1;
		}

		[[nodiscard]] Texture2D& texture() const{
			return *data;
		}
	};
}


