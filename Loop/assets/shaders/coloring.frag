#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform ivec3 backgroundColor;
uniform ivec3 foregroundColor;

out vec4 finalColor;

void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord) * fragColor;

    vec3 color3 = mix(backgroundColor / 255.0, foregroundColor / 255.0, texelColor.r);

    finalColor = vec4(color3, texelColor.a);
}
