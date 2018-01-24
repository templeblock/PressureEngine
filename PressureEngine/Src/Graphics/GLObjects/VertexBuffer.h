#pragma once

#include "../../Common.h"

namespace Pressure {

	class VertexBuffer {

	private:
		unsigned int m_ID;
		const unsigned int m_Type;

	public:
		VertexBuffer(const void* data, const unsigned int size, const unsigned int type = GL_FLOAT);
		~VertexBuffer();

		void bind() const;
		void unbind() const;

		void update(const void* data, const unsigned int size) const;
		void addInstancedAttribute(const unsigned int attribute, const unsigned int size, const unsigned int count, const unsigned int offset) const;		

	};

}