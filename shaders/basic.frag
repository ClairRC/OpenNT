#version 330 core

in vec2 fragTexCoords;
in vec2 fragTexScales;
in vec3 fragLightColor;
in vec3 fragLightPos;
in vec3 fragPos;

uniform sampler2D tex;

out vec4 FragColor;

void main()
{
    //Gets value from texture
    vec4 texColor = texture(tex, vec2(fragTexCoords.x * fragTexScales.x, fragTexCoords.y * fragTexScales.y));

    //Genuine bandaid fix for getting rid of the white background.
    //I will handle this better in the future. I JUST gotta make it look presentable for the prototype part i promise
    if (texColor.r > 0.8 && texColor.g > 0.8 && texColor.b > 0.8)
        discard;

    //Calculates lighting for remaining fragment
    vec3 ambientLight = vec3(0.08, 0.07, 0.23); //Hardcoding this for now
    vec3 fragNorm = vec3(0, 1, 0); //For now, I'm assuming the normal is directly in the y direction for testing
    vec3 lightDir = normalize(fragLightPos - fragPos);

    //Calculate diffuse light
    float angle = max(dot(fragNorm, lightDir), 0.0);
    vec3 diffuse = angle * fragLightColor;

    FragColor = texColor * (vec4(ambientLight, 1.0) + vec4(diffuse, 1.0));
} 
