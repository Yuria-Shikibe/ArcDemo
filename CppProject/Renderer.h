#pragma once
#include "Color.h"
#include "Events.h"
#include "FrameBuffer.h"

namespace Graphic{
	inline Events::Draw draw_post;
	inline Events::Draw_Prepare draw_prepare;
	inline Events::Draw_After draw_after;

	class Renderer
	{
	protected:
		std::vector<FrameBuffer*> screenSizeSyncFrameBuffers;

	public:
		int width, height;
		FrameBuffer* defaultFrameBuffer = nullptr;
		FrameBuffer* contextFrameBuffer = nullptr; //TODO uses stack to impl multi layer

		Renderer(const int w, const int h);

		~Renderer();

		void frameBegin(FrameBuffer& frameBuffer, const bool resize = false, const Color& initColor = Colors::CLEAR, const GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		void frameEnd();

		void resize(const int w, const int h);

		void draw();

		void drawMain();

		void postToScreen();

		void registerSizeSyncFrames(FrameBuffer& frameBuffer){
			screenSizeSyncFrameBuffers.push_back(&frameBuffer);
		}

		void removeSizeSyncFrames(FrameBuffer& frameBuffer){
			std::erase(screenSizeSyncFrameBuffers, &frameBuffer);
		}
	};

	inline Renderer* renderer;

	inline void initRenderer(const int w, const int h){
		renderer = new Renderer{w, h};
	}

	inline Renderer& getRenderer(){
		return *renderer;
	}
}


