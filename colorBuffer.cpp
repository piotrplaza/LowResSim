#include "colorBuffer.hpp"

ColorBuffer::ColorBuffer(glm::ivec2 res) : res(res)
{
	colorBuffer.resize(res.x * res.y, { 0.0f, 0.0f, 0.0f });
}

void ColorBuffer::putColor(glm::ivec2 pos, glm::vec3 color)
{
	assert(pos.x >= 0 && pos.x < res.x);
	assert(pos.y >= 0 && pos.y < res.y);

	colorBuffer[pos.y * res.x + pos.x] = color;
}

glm::vec3 ColorBuffer::getColor(glm::ivec2 pos) const
{
	assert(pos.x >= 0 && pos.x < res.x);
	assert(pos.y >= 0 && pos.y < res.y);

	return colorBuffer[pos.y * res.x + pos.x];
}

const glm::vec3& ColorBuffer::data() const
{
	return colorBuffer[0];
}

glm::ivec2 ColorBuffer::getRes() const
{
	return res;
}
