#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_CameraVP;
uniform mat4 u_Transform;
			
out vec2 v_TexCoord;

void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position = u_CameraVP * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 o_Color;

in vec2 v_TexCoord;

uniform float u_Visibility;
uniform sampler2D u_Texture;

void main()
{
	o_Color = u_Visibility * texture(u_Texture, v_TexCoord);
}