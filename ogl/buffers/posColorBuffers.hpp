#pragma once

#include <GL/glew.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace Buffers
{
	class PosColorBuffers
	{
	public:
		PosColorBuffers();
		PosColorBuffers(const PosColorBuffers&) = delete;
		PosColorBuffers(PosColorBuffers&& other) noexcept;
		~PosColorBuffers();

		void setPositionBuffer(const glm::vec2& data, size_t numOfPositions, GLenum positionsDataUsage);
		void setColorBuffer(const glm::vec3& data, size_t numOfColors, GLenum colorsDataUsage);
		void bindVertexArray() const;

		size_t getNumOfVertices() const;

	private:
		GLuint vertexArray;
		GLuint positionBuffer;
		GLuint colorBuffer;

		size_t numOfPositions = 0;
		size_t numOfColors = 0;

		size_t numOfAllocatedPositions = 0;
		size_t numOfAllocatedColors = 0;

		GLenum positionsDataUsage = GL_STATIC_DRAW;
		GLenum colorsDataUsage = GL_STATIC_DRAW;

		bool expired = false;
	};
}
