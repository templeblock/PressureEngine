#pragma once

#include <vector>
#include "VertexBuffer.h"
#include "../../DllExport.h"

namespace Pressure {

	struct VertexBufferElement {
		VertexBuffer buffer;
		unsigned int type;
		unsigned int count;
		bool normalized;
	};

	class PRESSURE_API VertexBufferLayout {

	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;

	public:
		VertexBufferLayout()
			: m_Stride(0) { }

		template<typename T>
		void push(const unsigned int count, const VertexBuffer& buffer) {
			static_assert(false);
		}

		template<>
		void push<float>(const unsigned int count, const VertexBuffer& buffer) {
			m_Elements.push_back({ buffer, GL_FLOAT, count, false });
			m_Stride += count * sizeof(float);
		}

		inline std::vector<VertexBufferElement>& getElements() const { return (std::vector<VertexBufferElement>&)m_Elements; }
		inline unsigned int getStride() const { return m_Stride; }		

	};

}