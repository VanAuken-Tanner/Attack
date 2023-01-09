#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textureCoord; 
layout(location = 2) in float textureId;

out vec2 v_TextureCoord;
out float v_TextureId;

uniform mat4 u_ModelViewProjection;

void main()
{
   //gl_Position = position;
   //gl_Position = position * u_ModelViewProjection;
   gl_Position = u_ModelViewProjection * position;//!!! This multiplication order matters!!!
   v_TextureCoord = textureCoord;
   v_TextureId = textureId;
};