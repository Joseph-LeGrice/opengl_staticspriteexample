#version 330

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec2 in_UV;

out vec2 fragmentUV;

uniform mat4 ModelViewProjection;

void main() 
{
    gl_Position = ModelViewProjection * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
	fragmentUV = in_UV;
}