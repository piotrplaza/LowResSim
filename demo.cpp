#include "demo.hpp"

#include "colorBuffer.hpp"

void Demo(ColorBuffer& colorBuffer)
{
	colorBuffer.putColor({ 0, 0 }, { 1, 1, 1 });
	colorBuffer.putColor({ 1, 0 }, { 1, 0, 0 });
	colorBuffer.putColor({ 0, 1 }, { 0, 1, 0 });
	colorBuffer.putColor({ 1, 1 }, { 0, 0, 1 });
}
