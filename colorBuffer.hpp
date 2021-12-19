#include <vector>

#include <glm/glm.hpp>

class ColorBuffer
{
public:
	enum class Bottom {Down, Left, Up, Right};
	ColorBuffer(glm::ivec2 res, Bottom bottom = Bottom::Down);

	void clear(glm::vec3 color = {0.0f, 0.0f, 0.0f});
	void putColor(glm::ivec2 pos, glm::vec3 color);
	glm::vec3 getColor(glm::ivec2 pos) const;
	const glm::vec3& data() const;
	glm::ivec2 getRes() const;
	void setBottom(Bottom bottom);
	Bottom getBottom() const;

private:
	void updateRes(Bottom bottom);
	const glm::vec3& colorBufferTransformedLocation(glm::ivec2 pos) const;
	glm::vec3& colorBufferTransformedLocation(glm::ivec2 pos);

	glm::ivec2 res;
	Bottom bottom;
	std::vector<glm::vec3> colorBuffer;
};
