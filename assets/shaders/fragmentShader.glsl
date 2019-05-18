#version 330 core

in vec2 texCoords;

out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{
    vec4 tex = texture(image, texCoords);
    if(tex.a == 0)
        discard;
    color = tex * vec4(spriteColor, 1.0);
}
