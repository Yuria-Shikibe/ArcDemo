#include "Blending.h"

Graphic::Blending::Blending(const GLenum src, const GLenum dst, const GLenum srcAlpha, const GLenum dstAlpha): src(src),
	dst(dst),
	srcAlpha(srcAlpha),
	dstAlpha(dstAlpha){
}

Graphic::Blending::Blending(const Blending& other) = default;

Graphic::Blending::Blending(Blending&& other) noexcept: src(other.src),
                                                                  dst(other.dst),
                                                                  srcAlpha(other.srcAlpha),
                                                                  dstAlpha(other.dstAlpha){
}

Graphic::Blending& Graphic::Blending::Blending::operator=(const Blending& other){
	if(this == &other) return *this;
	src = other.src;
	dst = other.dst;
	srcAlpha = other.srcAlpha;
	dstAlpha = other.dstAlpha;
	return *this;
}

Graphic::Blending& Graphic::Blending::Blending::operator=(Blending&& other) noexcept{
	if(this == &other) return *this;
	src = other.src;
	dst = other.dst;
	srcAlpha = other.srcAlpha;
	dstAlpha = other.dstAlpha;
	return *this;
}

bool Graphic::operator==(const Blending& lhs, const Blending& rhs){
	return &lhs == &rhs;
}

bool Graphic::operator!=(const Blending& lhs, const Blending& rhs){
	return !(lhs == rhs);
}

void Graphic::Blending::apply() const{
	glEnable(GL_BLEND);
	glBlendFuncSeparate(src, dst, srcAlpha, dstAlpha);
}
