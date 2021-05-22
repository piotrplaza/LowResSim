#include "posColorBuffers.hpp"

#include <cassert>

namespace Buffers
{
	PosColorBuffers::PosColorBuffers()
	{
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &positionBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &colorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(1);
	}

	PosColorBuffers::PosColorBuffers(PosColorBuffers&& other) noexcept:
		vertexArray(other.vertexArray),
		positionBuffer(other.positionBuffer),
		colorBuffer(other.colorBuffer)
	{
		other.expired = true;
	}

	PosColorBuffers::~PosColorBuffers()
	{
		if (expired) return;

		glDeleteBuffers(1, &positionBuffer);
		glDeleteBuffers(1, &colorBuffer);
		glDeleteVertexArrays(1, &vertexArray);
	}

	void PosColorBuffers::setPositionBuffer(const glm::vec2& data, size_t numOfPositions, GLenum positionsDataUsage)
	{
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
		if (numOfAllocatedPositions < numOfPositions || this->positionsDataUsage != positionsDataUsage)
		{
			glBufferData(GL_ARRAY_BUFFER, numOfPositions * sizeof(data), &data, positionsDataUsage);
			this->numOfAllocatedPositions = numOfPositions;
			this->positionsDataUsage = positionsDataUsage;
		}
		else
		{
			glBufferSubData(GL_ARRAY_BUFFER, 0, numOfPositions * sizeof(data), &data);
		}
		this->numOfPositions = numOfPositions;
		this->positionsDataUsage = positionsDataUsage;
	}

	void PosColorBuffers::setColorBuffer(const glm::vec3& data, size_t numOfColors, GLenum colorsDataUsage)
	{
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		if (numOfAllocatedColors < numOfColors || this->colorsDataUsage != colorsDataUsage)
		{
			glBufferData(GL_ARRAY_BUFFER, numOfColors * sizeof(data), &data, colorsDataUsage);
			this->numOfAllocatedColors = numOfColors;
			this->colorsDataUsage = colorsDataUsage;
		}
		else
		{
			glBufferSubData(GL_ARRAY_BUFFER, 0, numOfColors * sizeof(data), &data);
		}
		this->numOfColors = numOfColors;
		this->colorsDataUsage = colorsDataUsage;
	}

	void PosColorBuffers::bindVertexArray() const
	{
		glBindVertexArray(vertexArray);
	}

	size_t PosColorBuffers::getNumOfVertices() const
	{
		assert(numOfPositions == numOfColors);
		return numOfPositions;
	}
}
