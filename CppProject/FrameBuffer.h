#pragma once
#include <glad/glad.h>

#include "AbstractBuffer.h"
#include "RenderBuffer.h"
#include "Texture2D.h"

using namespace Graphic;

namespace Graphic{
	class FrameBuffer : virtual public AbstractBuffer
	{
	protected:
		int width = 0, height = 0;
		Texture2D* sample = nullptr;
		RenderBuffer* renderBuffer = nullptr;

	public:
		FrameBuffer(const int w, const int h);

		FrameBuffer() = default;

		~FrameBuffer() override;

		void resize(const int w, const int h);

		bool check() const;

		void bind() const override;

		void unbind() const override;

		Texture2D& getTexture() const;

		GLuint getTextureID() const;
	};


}
