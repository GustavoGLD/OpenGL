//-----------------------------------------------
//Esse aquivo cuidará dos vértices que passarmos
//-----------------------------------------------

//-----------------------------
//Versão do OpenGL a ser usada
#version 330 core

//-----------------------------------
//Passar vértice no índice 0 da VAO
layout (location = 0) in vec3 aPos;

//-----------------------------------
//Passar vértice no índice 1 da VAO
layout (location = 1) in vec3 aColor;

//---------------------------------------
//Cor que será passada para à fragShader
out vec3 ourColor;

//-----------
void main()
{
    //-------------------------------------
    //Declarar a posição final do vértice
    gl_Position = vec4(aPos, 1.0);

    //---------------------------------------------
    //Definir a cor que será passada à fragShader
    ourColor = aColor;
    
}