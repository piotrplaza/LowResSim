#include <vector>

#include <glm/glm.hpp>

class ColorBuffer
{
public:
	ColorBuffer(glm::ivec2 res);

	void putColor(glm::ivec2 pos, glm::vec3 color);
	glm::vec3 getColor(glm::ivec2 pos) const;
	const glm::vec3& data() const;
	glm::ivec2 getRes() const;

private:
	const glm::ivec2 res;
	std::vector<glm::vec3> colorBuffer;
};
