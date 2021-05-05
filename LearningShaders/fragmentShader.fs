//----------------------------------------------
//Esse arquivo cuidará das cores que passarmos
//----------------------------------------------

//-----------------------------
//Versão do OpenGL a ser usada
#version 330 core

//-------------------------
//Variavel com a Cor final
out vec4 FragColor;

//-----------------------------
//Cor que vertexShader passou
in vec3 ourColor;

//-----------
void main()
{
    //--------------------------------------
    //Definindo a variavel com a cor final
    FragColor = vec4(ourColor, 1.0f);
    
}