#version 330 core
out vec4 FragColor;

//in vec2 texCoord;
in vec3 vertexColor;

//uniform sampler2D texture1;
//uniform sampler2D texture2;

uniform float imageRatio;
uniform mat4 transform;

void main()
{
    FragColor = vec4(vertexColor, 1.0f);
}