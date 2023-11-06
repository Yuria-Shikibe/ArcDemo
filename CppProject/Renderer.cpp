#include "Renderer.h"

#include "Core.h"
#include "Draw.h"
#include "GraphicUtil.h"

Renderer::Renderer(const int w, const int h): width(w), height(h){
	defaultFrameBuffer = new FrameBuffer{};

	contextFrameBuffer = defaultFrameBuffer;
}

Renderer::~Renderer(){
	delete defaultFrameBuffer;
}

void Renderer::frameBegin(FrameBuffer& frameBuffer, const bool resize, const Color& initColor, const GLbitfield mask){
	if (contextFrameBuffer != defaultFrameBuffer)throw GL_Exception{ "Illegal FrameBuffer Apply!" };

	contextFrameBuffer = &frameBuffer;

	if(resize){
		contextFrameBuffer->resize(width, height);
	}

	contextFrameBuffer->bind();

	glClearColor(initColor.r, initColor.g, initColor.b, initColor.a);
	glClear(mask);
}

void Renderer::frameEnd(){
	if(contextFrameBuffer == defaultFrameBuffer)return;

	Draw::flush();

	defaultFrameBuffer->bind();

	glBindFramebuffer(GL_READ_FRAMEBUFFER, contextFrameBuffer->getID());
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, defaultFrameBuffer->getID());
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	// const Geom::Matrix3D* lastPorj = Core::batch->getProjection();
	//
	// // glDisable(GL_DEPTH_TEST);
	//
	// Core::batch->setProjection(Draw::MAT_IDT);
	// Draw::post(contextFrameBuffer->getTexture());
	// Draw::flush();
	//
	// // glEnable(GL_DEPTH_TEST);
	//
	// Core::batch->setProjection(*lastPorj);

	contextFrameBuffer = defaultFrameBuffer;
}

void Renderer::resize(const int w, const int h){
	width = w;
	height = h;

	for(const auto & frameBuffer : screenSizeSyncFrameBuffers){
		frameBuffer->resize(w, h);
	}
}

void Renderer::draw(){
	defaultFrameBuffer->bind();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Events::generalUpdateEvents.fire(draw_prepare);

	drawMain();

	Events::generalUpdateEvents.fire(draw_post);

	Events::generalUpdateEvents.fire(draw_after);
}

void Renderer::drawMain(){
			
}

void Renderer::postToScreen(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
