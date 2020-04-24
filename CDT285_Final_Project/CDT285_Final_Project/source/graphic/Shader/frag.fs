#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;
uniform bool renderTexture;
uniform vec3 renderColor;

void main()
{    
    if (renderTexture)
        FragColor = texture(texture1, TexCoords);
    else
        FragColor = vec4(renderColor, 1.0);
}