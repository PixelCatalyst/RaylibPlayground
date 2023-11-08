#version 330

in vec2 fragTexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec2 origin = vec2(0.5);
uniform float radius = 0.2;

out vec4 finalColor;

void main()
{
    vec4 backgroundTexel = texture(texture0, fragTexCoord);
    vec4 foregroundTexel = texture(texture1, fragTexCoord);

    float edge = radius * 0.005;
    float fade = 1.0 - smoothstep(radius - edge, radius + edge, distance(fragTexCoord, origin));

    finalColor = mix(backgroundTexel, foregroundTexel, fade);
}
