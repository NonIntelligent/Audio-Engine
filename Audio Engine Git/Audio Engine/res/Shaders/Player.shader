#shader vertex
#version 430 core

layout(location = 0) in vec3 position;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

void main()
{
	gl_Position = u_projection * vec4(position, 1.0);
	gl_Position = u_projection * u_view * vec4(position, 1.0);
	gl_Position = vec4(position, 1.0);
};

#shader fragment
#version 430 core

layout(location = 0) out vec4 colour;

uniform vec4 u_Colour;

void main()
{
	colour = u_Colour;
};