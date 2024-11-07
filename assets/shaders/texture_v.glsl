#version 460

layout(location = 0) in vec3 vertex_pos;

uniform mat4 MVP;

void main()
{
    gl_Position = vec4(vertex_pos, 1.0);
    // gl_Position = MVP * vec4(vertex_pos, 1.0);
}