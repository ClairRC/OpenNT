#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec2 texScale;
uniform vec3 lightPos;
uniform vec3 lightColor;

out vec2 fragTexCoords;
out vec2 fragTexScales;
out vec3 fragLightPos;
out vec3 fragLightColor;
out vec3 fragPos;

void main()
{
    //Send in the fragment world position, useful for lighting
    vec4 fragWorldPos = model * vec4(aPos.xyz, 1.0);
    fragPos = fragWorldPos.xyz;

    //Lighting stuff
    fragLightPos = lightPos;
    fragLightColor = lightColor;

    //Texture scaling and coords to the fragment shader
    fragTexScales = texScale;
    fragTexCoords = texCoords;
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}