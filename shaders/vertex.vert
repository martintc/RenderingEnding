#version 330 core
layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aColor;

// out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
   // gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
  gl_Position = proj * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   // color = aColor;
   // color = vec3(0.5, 0.5, 0.5);
}
