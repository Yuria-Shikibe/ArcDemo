#pragma once
#include "Batch.h"
#include "GL_Exception.h"

namespace Graphic{
	class SpriteBatch final : virtual public Batch
	{
	protected:
		int maxSize;
		float* cachedVertices = nullptr;
		GLuint* indexRef = nullptr;

	public:
		explicit SpriteBatch(const int verticesCount, Shader* shader): maxSize(verticesCount * VERT_GROUP_SIZE){
			constexpr int ELEM_LEN = IndexBuffer::ELEMENTS_STD_LENGTH;

			if (verticesCount > INT32_MAX / ELEM_LEN - 1)throw GL_Exception{ "Exceed Vertices Count!" };

			try{
				cachedVertices = new float[maxSize]{0};
				indexRef = new GLuint[verticesCount * ELEM_LEN];  // NOLINT(bugprone-implicit-widening-of-multiplication-result)
			}catch(const std::bad_alloc& alloc){
				throw GL_Exception{ alloc.what()};
			}

			const auto& begin = IndexBuffer::ELEMENTS_STD.cbegin(), end = IndexBuffer::ELEMENTS_STD.cend();

			for(int i = 0; i < verticesCount; i++){
				for(int j = 0; j < ELEM_LEN; ++j){
					indexRef[j + i * ELEM_LEN] = IndexBuffer::ELEMENTS_STD[j] + i * VERT_GROUP_COUNT;
				}
			}

			mesh = new Mesh();

			mesh->getIndexBuffer().bind();
			mesh->getIndexBuffer().setDataRaw(indexRef, verticesCount * ELEM_LEN);
			mesh->getVertexBuffer().bind();
			mesh->getVertexBuffer().setDataRaw(cachedVertices, sizeof(float) * maxSize);

			AttributeLayout layout;
			layout.addFloat(2); //Position 2D
			layout.addFloat(2); //UV offset
			layout.addFloat(4); //mix rgba
			layout.addFloat(4); //src rgba

			mesh->getVertexArray().bind();
			mesh->getVertexArray().addBuffer(mesh->getVertexBuffer(), layout);

			generalShader = shader;
			generalShader->bind();
			generalShader->registerUniform("u_texture");
			generalShader->registerUniform("view");

			generalShader->setUniformer([this](const Shader& s) -> void {
				s.setTexture2D("u_texture", *lastTexture);
				s.setMat3("view", *projection);
			});
		}

		SpriteBatch() : SpriteBatch(INT16_MAX / 4, new Shader("screenspace")){
			
		}

		~SpriteBatch() override{
			delete cachedVertices;
			delete indexRef;
		}

		void flush() override{
			if(index == 0)return;

			glDepthMask(false);

			mesh->getVertexBuffer().bind();
			mesh->getVertexBuffer().setDataRaw(cachedVertices, sizeof(float) * index);

			blending->apply();

			bindShader();
			applyShader();

			mesh->render(min(index / IndexBuffer::ELEMENTS_STD_LENGTH + 1, mesh->getIndexBuffer().getSize()));

			index = 0;
		}

		void post(const Texture2D& texture, float* vertices, const int length, const int offset, const int count) override{
			if(lastTexture != &texture){
				flush();
				lastTexture = &texture;
			}

			if(index + count > maxSize){
				flush();
			}

			std::copy_n(vertices + offset, count, cachedVertices + index);

			index += count;
		}
	};
}


