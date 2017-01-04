#version 330

in vec2 fragmentUV;

out vec4 fragmentColor;

uniform sampler2D atlasTexture;

void main() 
{
    fragmentColor = texture(atlasTexture, fragmentUV).rgba;
}