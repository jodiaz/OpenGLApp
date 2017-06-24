#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexture;

out vec3 ourColor;
out vec2 textureCoord;

void main (){
	gl_Position = vec4(position, 1.0);
	ourColor = aColor;
	textureCoord = aTexture;
}