#include "demo.hpp"

#include "colorBuffer.hpp"
#include "tools/utility.hpp"

void Demo(ColorBuffer& colorBuffer)
{
	for (int x = 0; x < colorBuffer.getRes().x; ++x)
	{
		colorBuffer.putColor({ x, 0 }, { Tools::Random(-10.0f, 10.0f), Tools::Random(-10.0f, 10.0f), Tools::Random(-5.0f, 5.0f) });
	}

	for (int y = 1; y < colorBuffer.getRes().y; ++y)
	{
		for (int x = 1; x < colorBuffer.getRes().x - 1; ++x)
		{
			glm::vec3 newColor = (colorBuffer.getColor({ x - 1, y - 1 }) + colorBuffer.getColor({ x, y - 1 }) + colorBuffer.getColor({ x + 1, y - 1 }) + colorBuffer.getColor({ x, y })) / 4.03f;
			colorBuffer.putColor({ x, y }, newColor);
		}
	}
}
