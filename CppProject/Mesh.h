#pragma once

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

namespace Graphic{
	class Mesh
	{
	public:
		VertexBuffer* vertexBuffer = nullptr;
		IndexBuffer* indexBuffer = nullptr;

		VertexArray* vertexArray = nullptr;

		Mesh(){
            vertexBuffer = new VertexBuffer();
            indexBuffer = new IndexBuffer();
            vertexArray = new VertexArray();
		}

		~Mesh(){
			delete vertexBuffer;
			delete indexBuffer;
			delete vertexArray;
		}

		Mesh(const Mesh& other) = delete;

		Mesh(Mesh&& other) = delete;

		Mesh& operator=(const Mesh& other) = delete;

		Mesh& operator=(Mesh&& other) = delete;

		[[nodiscard]] VertexBuffer& getVertexBuffer() const{
			return *vertexBuffer;
		}

		[[nodiscard]] IndexBuffer& getIndexBuffer() const{
			return *indexBuffer;
		}

		[[nodiscard]] VertexArray& getVertexArray() const{
			return *vertexArray;
		}

		void bind() const{
			vertexBuffer->bind();
			indexBuffer->bind();
			vertexArray->bind();
		}

		template <size_t size>
		Mesh& setVertices(float(&arr)[size]) {
            vertexBuffer->bind();

            vertexBuffer->setData(arr);

            return *this;
        }

        Mesh& setVertices(const float* arr, const int offset, const int count) {
            vertexBuffer->bind();

            vertexBuffer->setData(arr + offset, count);

            return *this;
        }

        void render(const int primitiveType, const int offset, const int count) const{
            if (indexBuffer != nullptr && indexBuffer->getSize() > 0) {
				indexBuffer->bind();
                glDrawElements(primitiveType, count, GL_UNSIGNED_INT, reinterpret_cast<const void*>(offset * sizeof(GLuint)));
            }
            else {
				vertexBuffer->bind();
                glDrawArrays(primitiveType, offset, count);
            }
        }

		void render(const int count) const{
			render(GL_TRIANGLES, 0, count);
		}
	};
}


