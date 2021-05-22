#version 440

in vec2 bPos;
in vec3 bColor;

out vec3 vColor;

void main()
{
	gl_Position = vec4(bPos, 0.0, 1.0);
	vColor = bColor;
}
