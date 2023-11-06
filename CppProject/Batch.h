#pragma once
#include <functional>

#include "Blending.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture2D.h"

namespace Graphic{
	static constexpr int VERT_GROUP_SIZE = 2 + 2 + 4 + 4;
	static constexpr int VERT_GROUP_COUNT = 4;
	static constexpr int VERT_LENGTH_STD = VERT_GROUP_COUNT * (VERT_GROUP_SIZE);

	class Batch
	{
	protected:
		Mesh* mesh = nullptr;
		const Texture2D* lastTexture = nullptr;
		Shader* generalShader = nullptr;
		Shader* customShader = nullptr;

		const Blending* blending = &Blendings::NORMAL;

		const Geom::Matrix3D* projection = nullptr;

		bool autoDelete = true;
		int index = 0;

	public:
		Batch() = default;

		Batch(const Batch& other) = delete;

		Batch(Batch&& other) = delete;

		Batch& operator=(const Batch& other) = delete;

		Batch& operator=(Batch&& other) = delete;

		virtual void bindAll() const {
			mesh->bind();
		}

		[[nodiscard]] bool hasShader() const {
			return customShader || generalShader;
		}

		[[nodiscard]] bool applyCustomShader() const {
			return customShader;
		}

		[[nodiscard]] Shader& getGeneralShader() const {
			return *generalShader;
		}

		void setCustomShader(Shader& shader) {
			customShader = &shader;
			customShader->bind();
		}

		void setCustomShader() {
			customShader = nullptr;
			generalShader->bind();
		}

		void switchShader(Shader& shader) {
			flush();

			setCustomShader(shader);
		}

		void clearCustomShader(const bool flushContext = true) {
			if(flushContext)flush();

			customShader = nullptr;
			generalShader->bind();
		}

		void switchBlending(const Blending& b){
			if(blending != &b){
				flush();
			}

			blending = &b;
		}

		void setProjection(const Geom::Matrix3D& porj){
			projection = &porj;
		}

		const Geom::Matrix3D* getProjection() const{
			return projection;
		}

		void bindShader() const{
			if(applyCustomShader()){
				customShader->bind();
			}else{
				generalShader->bind();
			}
		}

		void applyShader() const{
			if(applyCustomShader()){
				customShader->apply();
			}else{
				generalShader->apply();
			}
		}

		virtual ~Batch(){
			if(autoDelete){
				delete mesh;
				delete generalShader;
			}
		}

		virtual void flush() = 0;

		virtual void post(const Texture2D& texture, float* vertices, int length, int offset, int count) = 0;

		virtual void post(const std::function<void()>& drawPost){
			drawPost();
		}
	};
}


