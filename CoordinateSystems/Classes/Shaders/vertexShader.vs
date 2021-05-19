//======================================================================================
// *** Essa Shader será a instrução à GPU para cada Vértice do nosso Retângulo  ***
// *** O OpenGL Interpolation usará aqui como base para o restante do Retângulo ***
//======================================================================================

//----------------------------------------------------------------------------
//Versão do OpenGL
#version 330 core

//----------------------------------------------------------------------------
//Input. Coordenada do nosso vértice
layout (location = 0) in vec3 aPos;

//----------------------------------------------------------------------------
//Input. Cor do nosso vértice (Opcional. Você pode ignorar, temos textura)
layout (location = 1) in vec3 aColor;

//----------------------------------------------------------------------------
//Input. Coordenada na textura que corresponde ao vértice
layout (location = 2) in vec2 aTexCoord;

//----------------------------------------------------------------------------
//Output. A cor e textura do vértice erá enviada para a Fragment Shader
out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    //------------------------------------------------------------------------
    //Definindo a coordenada final do vértice
	gl_Position = projection * view * model * vec4(aPos, 1.0);

    //------------------------------------------------------------------------
    //Definindo a cor do vértice que vai para a Fragment Shader
	ourColor = aColor;

    //------------------------------------------------------------------------
    //Definindo a textura do vértice que vai para a Fragment Shader
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}