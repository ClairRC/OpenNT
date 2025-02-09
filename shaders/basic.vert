#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;

out vec4 fragColor;

//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;

uniform mat4 trans;

void main()
{
    fragColor = vec4(color, 1.0);

    //mat4 transformation = projection * view * model;

    gl_Position = trans * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}