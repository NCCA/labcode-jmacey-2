#version 410 core

layout (location=0) out vec4 fragColour;
in vec3 particle_colour;
void main()
{
    fragColour=vec4(particle_colour,1.0);
}