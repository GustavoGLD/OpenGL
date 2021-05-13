//============================================================================================
// *** Essa Shader será a instrução à GPU para cor de cada Vértice do nosso Retângulo ***
// *** O OpenGL Interpolation usará aqui como base para o restante do Retângulo       ***
//============================================================================================

//---------------------------------------------------------------------------------------------
//Versão do OpenGL
#version 330 core

//---------------------------------------------------------------------------------------------
//Definindo a cor final
out vec4 FragColor;

//---------------------------------------------------------------------------------------------
//Recebendo a cor do vértice vindo da Vertex Shader (opcional)
in vec3 ourColor;

//---------------------------------------------------------------------------------------------
//Recebendo a coordenada da textura que corresponde o vertice vinde da Vertex Shader
in vec2 TexCoord;

//---------------------------------------------------------------------------------------------
//Sampler2D da nossa Textura
uniform sampler2D texture1;

void main()
{
    //-----------------------------------------------------------------------------------------
    //Definindo a cor final do pixel referente ao vértice
    //(uma mistura da cor dada [opcional] com a textura)
	FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);
}