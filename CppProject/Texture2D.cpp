#include "Texture2D.h"

#include "Graphic.h"
#include "image.h"


Graphic::Texture2D::~Texture2D(){
	glDeleteTextures(1, &textureID);
}

Graphic::Texture2D::Texture2D(const int w, const int h): width(w), height(h){
	glGenTextures(1, &textureID);
	bind();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glGenerateMipmap(GL_TEXTURE_2D);
	setParametersDef();
}

Graphic::Texture2D::Texture2D(const std::string& name){
	loadFromFile(name);
	texName = name;
}

std::size_t Graphic::hashCode(const Texture2D& obj){
	return obj.textureID;
}

std::ostream& Graphic::operator<<(std::ostream& os, const Texture2D& obj){
	return os << "texName: " << obj.texName;
}

bool Graphic::operator==(const Texture2D& lhs, const Texture2D& rhs){
	return lhs.texName == rhs.texName;
}

bool Graphic::operator!=(const Texture2D& lhs, const Texture2D& rhs){
	return !(lhs == rhs);
}

Graphic::Texture2D::Texture2D(const Texture2D& other): texName(other.texName),
                                                       textureID(other.textureID),
                                                       width(other.width),
                                                       height(other.height),
                                                       bpp(other.bpp){
}

Graphic::Texture2D::Texture2D(Texture2D&& other) noexcept: localData(other.localData),
                                                           texName(std::move(other.texName)),
                                                           textureID(other.textureID),
                                                           width(other.width),
                                                           height(other.height),
                                                           bpp(other.bpp){
}

Graphic::Texture2D& Graphic::Texture2D::operator=(const Texture2D& other){
	if(this == &other) return *this;
	texName = other.texName;
	textureID = other.textureID;
	width = other.width;
	height = other.height;
	bpp = other.bpp;
	return *this;
}

Graphic::Texture2D& Graphic::Texture2D::operator=(Texture2D&& other) noexcept{
	if(this == &other) return *this;
	texName = std::move(other.texName);
	textureID = other.textureID;
	width = other.width;
	height = other.height;
	bpp = other.bpp;
	return *this;
}

void Graphic::Texture2D::resize(const int w, const int h){
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, localData);
	width = w;
	height = h;
	unbind();
}

void Graphic::Texture2D::loadFromFile(const std::string& name){
	stbi_set_flip_vertically_on_load(1);

	localData = stbi_load(Graphic::getPath("texture\\" + name).data(), &width, &height, &bpp, 4);

	glGenTextures(1, &textureID);

	setParametersDef();

	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localData);
	glGenerateMipmap(GL_TEXTURE_2D);
	unbind();

	if (localData) {
		stbi_image_free(localData);
		localData = nullptr;
	}
}

void Graphic::Texture2D::setParametersDef() const{
	bind(false);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	unbind();
}

void Graphic::Texture2D::setScale(const GLint upScale, const GLint downScale) const{
	bind(false);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, downScale);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, upScale);
	unbind();
}

void Graphic::Texture2D::setWrap(const GLint clamp) const{
	bind(false);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clamp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clamp);
	unbind();
}

void Graphic::Texture2D::bind(const bool active, const unsigned char slotOffset) const{
	if (active)glActiveTexture(GL_TEXTURE0 + slotOffset);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture2D::bindParam(const GLenum target){
	glBindTexture(target, textureID);
}

void Graphic::Texture2D::unbind() const{
	glBindTexture(GL_TEXTURE_2D, 0);
}
