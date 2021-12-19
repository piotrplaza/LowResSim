#include "colorBuffer.hpp"

ColorBuffer::ColorBuffer(glm::ivec2 res, Bottom bottom) :
	res(res),
	bottom(Bottom::Down)
{
	colorBuffer.resize(res.x * res.y, { 0.0f, 0.0f, 0.0f });
	updateRes(bottom);
}

void ColorBuffer::clear(glm::vec3 color)
{
	std::fill(colorBuffer.begin(), colorBuffer.end(), color);
}

void ColorBuffer::putColor(glm::ivec2 pos, glm::vec3 color)
{
	assert(pos.x >= 0 && pos.x < res.x);
	assert(pos.y >= 0 && pos.y < res.y);

	colorBufferTransformedLocation(pos) = color;
}

glm::vec3 ColorBuffer::getColor(glm::ivec2 pos) const
{
	assert(pos.x >= 0 && pos.x < res.x);
	assert(pos.y >= 0 && pos.y < res.y);

	return colorBufferTransformedLocation(pos);
}

const glm::vec3& ColorBuffer::data() const
{
	return colorBuffer[0];
}

glm::ivec2 ColorBuffer::getRes() const
{
	return res;
}

void ColorBuffer::setBottom(Bottom bottom)
{
	updateRes(bottom);
	this->bottom = bottom;
}

ColorBuffer::Bottom ColorBuffer::getBottom() const
{
	return bottom;
}

void ColorBuffer::updateRes(Bottom bottom)
{
	if (((this->bottom == Bottom::Down || this->bottom == Bottom::Up) && (bottom == Bottom::Left || bottom == Bottom::Right))
		|| ((this->bottom == Bottom::Left || this->bottom == Bottom::Right) && (bottom == Bottom::Down || bottom == Bottom::Up)))
	{
		res = { res.y, res.x };
	}
}

const glm::vec3& ColorBuffer::colorBufferTransformedLocation(glm::ivec2 pos) const
{
	switch (bottom)
	{
	case Bottom::Down:
		return colorBuffer[pos.y * res.x + pos.x];
	case Bottom::Left:
		return colorBuffer[(res.x - 1 - pos.x) * res.y + pos.y];
	case Bottom::Up:
		return colorBuffer[(res.y - 1 - pos.y) * res.x + (res.x - 1 - pos.x)];
	case Bottom::Right:
		return colorBuffer[pos.x * res.y + (res.y - 1 - pos.y)];
	}

	return colorBuffer[0];
}

glm::vec3& ColorBuffer::colorBufferTransformedLocation(glm::ivec2 pos)
{
	return const_cast<glm::vec3&>(static_cast<const ColorBuffer*>(this)->colorBufferTransformedLocation(pos));
}
