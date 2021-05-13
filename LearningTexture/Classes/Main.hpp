#include "../Libs/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "../Classes/Buffers.hpp"
#include "../Classes/Textures.hpp"

class Main : public Buffers, public Textures{
private:
    Shader ourShader;

public:
    inline void Start(){
        //---------------------------------------------------
        //Ler e compilar Shader; criar programa de Shaders
        ourShader.newShader("Classes/Shaders/vertexShader.vs", "Classes/Shaders/fragmentShader.fs");

        SettingUpBuffers();
        SettingUpTextures();
    }

    inline void Update(){
        //-------------------------------------------------------------------
        //Ligando a Textura, ShaderProgram, VAO e rederizando o Retangulo
        glBindTexture(GL_TEXTURE_2D, texture);
        glUseProgram(ourShader.ID);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    inline void Finish(){
        //----------------------------------------------------------------------
        //Deletando VAO, VBO e EBO para fechar o programa (opcional)
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

};