#version 460 core

layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec2 vertex_uv;

out vec2 frag_uv;

uniform mat4 MVP;

void main()
{
    frag_uv = vertex_uv;
    gl_Position = MVP * vec4(vertex_pos, 1.0);
}