#pragma once
#include "Core.h"
#include "Color.h"
#include "Texture2D.h"
#include "TextureRegion.h"

namespace Graphic::Draw{
	inline float vertices[VERT_LENGTH_STD] = {0};

	inline Color contextColor = Colors::WHITE;
	inline Color contextMixColor = Colors::WHITE;

	inline const TextureRegion* contextTexture = nullptr;
	inline const TextureRegion* defaultTexture = nullptr;

	inline float contextStroke = 1.0f;

	inline Matrix3D MAT_IDT;

	static Vector2D vec2_0;
	static Vector2D vec2_1;
	static Vector2D vec2_2;
	static Vector2D vec2_3;
	static Vector2D vec2_4;
	static Vector2D vec2_5;
	static Vector2D vec2_6;

	static void color(const Color& color){
		contextColor = color;
	}

	static void mixColor(const Color& color) {
		contextMixColor = color;
	}

	static void alpha(const float a){
		contextColor.setA(a);
	}

	static void color(const Color& c1, const Color& c2, const float t){
		contextColor.lerp({ c1, c2 }, t);
	}

	static void blend(const Blending& blending = Blendings::NORMAL){
		Core::batch->switchBlending(blending);
	}

	static void texture(const TextureRegion& texture = *defaultTexture){
		contextTexture = &texture;
	}

	static void defTexture(const TextureRegion& texture){
		defaultTexture = &texture;
	}

	static void flush(){
		Core::batch->flush();
	}

	static void shader(Shader& shader, const bool flushContext = true){
		if (flushContext)flush();

		Core::batch->setCustomShader(shader);
	}

	static void shader(const bool flushContext = true){
		Core::batch->clearCustomShader(flushContext);
	}


	static void vert(
		const Texture2D& texture,
		const float x1, const float y1, const float texSrc1, const float texDest1, const Color& c1, const Color& cm1, 
		const float x2, const float y2, const float texSrc2, const float texDest2, const Color& c2, const Color& cm2,
		const float x3, const float y3, const float texSrc3, const float texDest3, const Color& c3, const Color& cm3,
		const float x4, const float y4, const float texSrc4, const float texDest4, const Color& c4, const Color& cm4
	){
		vertices[0  + 0 * VERT_GROUP_SIZE] = x1;
		vertices[1  + 0 * VERT_GROUP_SIZE] = y1;
		vertices[2  + 0 * VERT_GROUP_SIZE] = texSrc1;
		vertices[3  + 0 * VERT_GROUP_SIZE] = texDest1;
		vertices[4  + 0 * VERT_GROUP_SIZE] = cm1.r;
		vertices[5  + 0 * VERT_GROUP_SIZE] = cm1.g;
		vertices[6  + 0 * VERT_GROUP_SIZE] = cm1.b;
		vertices[7  + 0 * VERT_GROUP_SIZE] = cm1.a;
		vertices[8  + 0 * VERT_GROUP_SIZE] = c1.r;
		vertices[9  + 0 * VERT_GROUP_SIZE] = c1.g;
		vertices[10 + 0 * VERT_GROUP_SIZE] = c1.b;
		vertices[11 + 0 * VERT_GROUP_SIZE] = c1.a;

		vertices[0  + 1 * VERT_GROUP_SIZE] = x2;
		vertices[1  + 1 * VERT_GROUP_SIZE] = y2;
		vertices[2  + 1 * VERT_GROUP_SIZE] = texSrc2;
		vertices[3  + 1 * VERT_GROUP_SIZE] = texDest2;
		vertices[4  + 1 * VERT_GROUP_SIZE] = cm2.r;
		vertices[5  + 1 * VERT_GROUP_SIZE] = cm2.g;
		vertices[6  + 1 * VERT_GROUP_SIZE] = cm2.b;
		vertices[7  + 1 * VERT_GROUP_SIZE] = cm2.a;
		vertices[8  + 1 * VERT_GROUP_SIZE] = c2.r;
		vertices[9  + 1 * VERT_GROUP_SIZE] = c2.g;
		vertices[10 + 1 * VERT_GROUP_SIZE] = c2.b;
		vertices[11 + 1 * VERT_GROUP_SIZE] = c2.a;

		vertices[0  + 2 * VERT_GROUP_SIZE] = x3;
		vertices[1  + 2 * VERT_GROUP_SIZE] = y3;
		vertices[2  + 2 * VERT_GROUP_SIZE] = texSrc3;
		vertices[3  + 2 * VERT_GROUP_SIZE] = texDest3;
		vertices[4  + 2 * VERT_GROUP_SIZE] = cm3.r;
		vertices[5  + 2 * VERT_GROUP_SIZE] = cm3.g;
		vertices[6  + 2 * VERT_GROUP_SIZE] = cm3.b;
		vertices[7  + 2 * VERT_GROUP_SIZE] = cm3.a;
		vertices[8  + 2 * VERT_GROUP_SIZE] = c3.r;
		vertices[9  + 2 * VERT_GROUP_SIZE] = c3.g;
		vertices[10 + 2 * VERT_GROUP_SIZE] = c3.b;
		vertices[11 + 2 * VERT_GROUP_SIZE] = c3.a;
				   
		vertices[0  + 3 * VERT_GROUP_SIZE] = x4;
		vertices[1  + 3 * VERT_GROUP_SIZE] = y4;
		vertices[2  + 3 * VERT_GROUP_SIZE] = texSrc4;
		vertices[3  + 3 * VERT_GROUP_SIZE] = texDest4;
		vertices[4  + 3 * VERT_GROUP_SIZE] = cm4.r;
		vertices[5  + 3 * VERT_GROUP_SIZE] = cm4.g;
		vertices[6  + 3 * VERT_GROUP_SIZE] = cm4.b;
		vertices[7  + 3 * VERT_GROUP_SIZE] = cm4.a;
		vertices[8  + 3 * VERT_GROUP_SIZE] = c4.r;
		vertices[9  + 3 * VERT_GROUP_SIZE] = c4.g;
		vertices[10 + 3 * VERT_GROUP_SIZE] = c4.b;
		vertices[11 + 3 * VERT_GROUP_SIZE] = c4.a;

		Core::batch->post(texture, vertices, VERT_LENGTH_STD, 0, VERT_LENGTH_STD);
	}

	static void vert(
		const Texture2D& texture,
		const float x1, const float y1, const Color& c1, const Color& cm1,
		const float x2, const float y2, const Color& c2, const Color& cm2,
		const float x3, const float y3, const Color& c3, const Color& cm3,
		const float x4, const float y4, const Color& c4, const Color& cm4
	) {
		vert(
			texture,
			x1, y1, 0.0f, 0.0f, c1, cm1,
			x2, y2, 0.0f, 1.0f, c2, cm2,
			x3, y3, 1.0f, 1.0f, c3, cm3,
			x4, y4, 1.0f, 0.0f, c4, cm4
		);
	}

	static void vert(
		const Texture2D& texture,
		const float x1, const float y1, const Color& c1,
		const float x2, const float y2, const Color& c2,
		const float x3, const float y3, const Color& c3,
		const float x4, const float y4, const Color& c4
	){
		vert(
			texture,
			x1, y1, 0.0f, 0.0f, c1, Colors::CLEAR,
			x2, y2, 0.0f, 1.0f, c2, Colors::CLEAR,
			x3, y3, 1.0f, 1.0f, c3, Colors::CLEAR,
			x4, y4, 1.0f, 0.0f, c4, Colors::CLEAR
		);
	}

	static void vert(
		const Texture2D& texture,
		const float x1, const float y1,
		const float x2, const float y2,
		const float x3, const float y3,
		const float x4, const float y4
	){
		vert(
			texture,
			x1, y1, 0.0f, 0.0f, Colors::WHITE, Colors::CLEAR,
			x2, y2, 0.0f, 1.0f, Colors::WHITE, Colors::CLEAR,
			x3, y3, 1.0f, 1.0f, Colors::WHITE, Colors::CLEAR,
			x4, y4, 1.0f, 0.0f, Colors::WHITE, Colors::CLEAR
		);
	}

	static void post(const Texture2D& texture) {
		vert(texture, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f);
	}

	static void vert(
		const Texture2D& texture,
		const Geom::Vector2D& v1,
		const Geom::Vector2D& v2,
		const Geom::Vector2D& v3,
		const Geom::Vector2D& v4
	) {
		vert(
			texture,
			v1.x, v1.y,
			v2.x, v2.y,
			v3.x, v3.y,
			v4.x, v4.y
		);
	}

	static void quad(const TextureRegion& region,
		const float x1, const float y1, const Color& c1,
		const float x2, const float y2, const Color& c2,
		const float x3, const float y3, const Color& c3,
		const float x4, const float y4, const Color& c4
	) {
		vert(
			*region.data,
			x1, y1, region.u0, region.v0, c1, contextMixColor,
			x2, y2, region.u0, region.v1, c2, contextMixColor,
			x3, y3, region.u1, region.v1, c3, contextMixColor,
			x4, y4, region.u1, region.v0, c4, contextMixColor
		);
	}

	static void quad(const TextureRegion& region,
		const float x1, const float y1,
		const float x2, const float y2,
		const float x3, const float y3,
		const float x4, const float y4
	) {
		vert(
			*region.data,
			x1, y1, region.u0, region.v0, contextColor, contextMixColor,
			x2, y2, region.u0, region.v1, contextColor, contextMixColor,
			x3, y3, region.u1, region.v1, contextColor, contextMixColor,
			x4, y4, region.u1, region.v0, contextColor, contextMixColor
		);
	}

	static void quad(
		const float x1, const float y1,
		const float x2, const float y2,
		const float x3, const float y3,
		const float x4, const float y4
	) {
		vert(
			*defaultTexture->data,
			x1, y1, defaultTexture->u0, defaultTexture->v0, contextColor, contextMixColor,
			x2, y2, defaultTexture->u0, defaultTexture->v1, contextColor, contextMixColor,
			x3, y3, defaultTexture->u1, defaultTexture->v1, contextColor, contextMixColor,
			x4, y4, defaultTexture->u1, defaultTexture->v0, contextColor, contextMixColor
		);
	}

	static void line(const TextureRegion& region, const float x, const float y, const float x2, const float y2, const bool cap = true) {
		const float h_stroke = contextStroke / 2.0f;
		const float len = Mathf::len(x2 - x, y2 - y);
		const float diff_x = (x2 - x) / len * h_stroke;
		const float diff_y = (y2 - y) / len * h_stroke;

		if (cap) {
			quad(
				region,

				x - diff_x - diff_y,
				y - diff_y + diff_x,

				x - diff_x + diff_y,
				y - diff_y - diff_x,

				x2 + diff_x + diff_y,
				y2 + diff_y - diff_x,

				x2 + diff_x - diff_y,
				y2 + diff_y + diff_x

			);
		}else {
			quad(
				region,

				x - diff_y,
				y + diff_x,

				x + diff_y,
				y - diff_x,

				x2 + diff_y,
				y2 - diff_x,

				x2 - diff_y,
				y2 + diff_x

			);
		}
	}

	static void stroke(const float s){
		contextStroke = s;
	}

	static void lineAngleCenter(const float x, const float y, const float angle, const float length, const bool cap = true) {
		vec2_0.setPolar(angle, length);

		line(*contextTexture, x - vec2_0.x / 2.0f, y - vec2_0.y / 2.0f, x + vec2_0.x / 2.0f, y + vec2_0.y / 2.0f, cap);
	}

	static void lineAngle(const float x, const float y, const float angle, const float length, const bool cap = true) {
		vec2_0.setPolar(angle, length);

		line(*contextTexture, x, y, x + vec2_0.x, y + vec2_0.y, cap);
	}

	static void lineAngle(const float x, const float y, const float angle, const float length) {
		vec2_0.setPolar(angle, length);

		line(*contextTexture, x, y, x + vec2_0.x, y + vec2_0.y);
	}

	static void lineAngle(const float x, const float y, const float angle, const float length, const float offset) {
		vec2_0.setPolar(angle, 1.0f);

		line(*contextTexture, x + vec2_0.x * offset, y + vec2_0.y * offset, x + vec2_0.x * (length + offset), y + vec2_0.y * (length + offset));
	}

	static void lineSquare(const float x, const float y, const float radius, float ang){
		ang += 45.000f;
		const float dst = contextStroke * Mathf::SQRT2 / 2.0f;

		vec2_0.setPolar(ang, 1);

		vec2_1.set(vec2_0).scl(radius - dst);
		vec2_2.set(vec2_0).scl(radius + dst);

		for(int i = 0; i < 4; ++i){
			vec2_0.rotateRT();

			vec2_3.set(vec2_0).scl(radius - dst);
			vec2_4.set(vec2_0).scl(radius + dst);

			quad(vec2_1.x + x, vec2_1.y + y, vec2_2.x + x, vec2_2.y + y, vec2_4.x + x, vec2_4.y + y, vec2_3.x + x, vec2_3.y + y);

			vec2_1.set(vec2_3);
			vec2_2.set(vec2_4);
		}
	}

	static void poly(const float x, const float y, const int sides, const float radius, const float angle) {
		const float space = 360.0f / static_cast<float>(sides);
		const float h_step = contextStroke / 2.0f / Mathf::cosDeg(space / 2.0f);
		const float r1 = radius - h_step;
		const float r2 = radius + h_step;

		for (int i = 0; i < sides; i++) {
			const float a = space * i + angle;
			const float cos1 = Mathf::cosDeg(a);
			const float sin1 = Mathf::sinDeg(a);
			const float cos2 = Mathf::cosDeg(a + space);
			const float sin2 = Mathf::sinDeg(a + space);
			quad(
				x + r1 * cos1, y + r1 * sin1,
				x + r1 * cos2, y + r1 * sin2,
				x + r2 * cos2, y + r2 * sin2,
				x + r2 * cos1, y + r2 * sin1
			);
		}
	}

	template <size_t size>
	static void poly(const float x, const float y, const int sides, const float radius, const float angle, const float ratio, const Color(&colorGroup)[size]) {
		const auto fSides = static_cast<float>(sides);

		const float space = 360.0f / fSides;
		const float h_step = contextStroke / 2.0f / Mathf::cosDeg(space / 2.0f);
		const float r1 = radius - h_step;
		const float r2 = radius + h_step;

		float currentRatio = 0;

		float currentAng = angle;
		float sin1 = Mathf::sinDeg(currentAng);
		float cos1 = Mathf::cosDeg(currentAng);
		float sin2, cos2;

		float progress = 0;
		Color lerpColor1 = colorGroup[0x000000];
		Color lerpColor2 = colorGroup[size - 1];

		for (;progress < fSides * ratio - 1.0f; progress += 1.0f){  // NOLINT(cert-flp30-c)
			currentAng = angle + (progress + 1.0f) * space;

			sin2 = Mathf::sinDeg(currentAng);
			cos2 = Mathf::cosDeg(currentAng);

			currentRatio = progress / fSides;

			lerpColor2.lerp(colorGroup, currentRatio);

			quad(*defaultTexture,
				cos1 * r1 + x, sin1 * r1 + y, lerpColor1,
				cos1 * r2 + x, sin1 * r2 + y, lerpColor1,
				cos2 * r2 + x, sin2 * r2 + y, lerpColor2,
				cos2 * r1 + x, sin2 * r1 + y, lerpColor2
			);

			lerpColor1.set(lerpColor2);

			sin1 = sin2;
			cos1 = cos2;
		}

		currentRatio = ratio;
		const float remainRatio = currentRatio * fSides - progress;

		currentAng = angle + (progress + 1.0f) * space;

		sin2 = Mathf::lerp(sin1, Mathf::sinDeg(currentAng), remainRatio);
		cos2 = Mathf::lerp(cos1, Mathf::cosDeg(currentAng), remainRatio);

		lerpColor2.lerp(colorGroup, progress / fSides).lerp(lerpColor1, 1.0f - remainRatio);

		quad(*defaultTexture,
			cos1 * r1 + x, sin1 * r1 + y, lerpColor1,
			cos1 * r2 + x, sin1 * r2 + y, lerpColor1,
			cos2 * r2 + x, sin2 * r2 + y, lerpColor2,
			cos2 * r1 + x, sin2 * r1 + y, lerpColor2
		);
	}
}
