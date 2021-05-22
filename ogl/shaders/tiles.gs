#version 440

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in vec3 vColor[];

out vec3 gColor;

uniform vec2 hSize = vec2(0.1);

void main()
{
    const vec4 position = vec4(gl_in[0].gl_Position.xy, 0.0, 1.0);

	gl_Position = position + vec4(-hSize.x, -hSize.y, 0.0, 0.0);
    gColor = vColor[0];
    EmitVertex();
    gl_Position = position + vec4(hSize.x, -hSize.y, 0.0, 0.0);
    gColor = vColor[0];
    EmitVertex();
    gl_Position = position + vec4(-hSize.x, hSize.y, 0.0, 0.0);
    gColor = vColor[0];
    EmitVertex();
    gl_Position = position + vec4(hSize.x, hSize.y, 0.0, 0.0);
    gColor = vColor[0];
    EmitVertex();

    EndPrimitive();
}
