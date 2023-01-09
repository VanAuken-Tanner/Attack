#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TextureCoord;
in float v_TextureId;

uniform vec4 u_Color;//a color var no longer used
uniform sampler2D u_Textures[2];//texture loaded into cpu from file path


void main()
{
   //color = vec4(0.0, 0.0, 1.0, 1.0);//rgba layout
   //color = u_Color;//rgba layout
   //                                     v_TextureCoord position coordinates passed from vertex shader
   int index = int(v_TextureId);
   vec4 textureColor = texture(u_Textures[index], v_TextureCoord);
   color = textureColor;
};
