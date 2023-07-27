#version 330

in vec2 fragTexCoord;

uniform sampler2D texture0;
uniform ivec3 backgroundColor;
uniform ivec3 foregroundColor;

out vec4 finalColor;

void main()
{
    vec4 foreground = vec4(foregroundColor / 255.0, 1.0);
    vec4 background = vec4(backgroundColor / 255.0, 1.0);

    vec4 texelColor = texture(texture0, fragTexCoord);

    finalColor = mix(background, foreground, texelColor.r);
}
