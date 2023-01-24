#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TextureCoord;
in float v_TextureId;

uniform vec4 u_Color;//a color var no longer used
uniform sampler2D u_Textures[6];//texture loaded into cpu from file path


void main()
{
   int index = int(v_TextureId);
   vec4 textureColor = texture(u_Textures[index], v_TextureCoord);
   color = textureColor;
};
