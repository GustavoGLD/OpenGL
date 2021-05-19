#include "../Libs/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "../Libs/glm/glm.hpp"
#include "../Libs/glm/gtc/matrix_transform.hpp"
#include "../Libs/glm/gtc/type_ptr.hpp"

#include "../Classes/Buffers.hpp"
#include "../Classes/Textures.hpp"

class Main : public Buffers, public Textures{
private:
    Shader ourShader;

public:
    inline void Start(GLFWwindow* window){
        //---------------------------------------------------
        //Ler e compilar Shader; criar programa de Shaders
        ourShader.newShader("Classes/Shaders/vertexShader.vs", "Classes/Shaders/fragmentShader.fs");

        SettingUpBuffers();
        SettingUpTextures();

        glEnable(GL_DEPTH_TEST);  

    }

    inline void Update(GLFWwindow* window){
        //-------------------------------------------------------------------
        //Ligando a Textura, ShaderProgram, VAO e rederizando o Retangulo
        glBindTexture(GL_TEXTURE_2D, texture);
        glUseProgram(ourShader.ID);

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view  = glm::mat4(1.0f);
        glm::mat4 proj  = glm::mat4(1.0f);

        float a = sinf(glfwGetTime()) / 2 + 0.5f;

        model = glm::rotate(model, glm::radians(360.0f * a), glm::vec3(1.0f, 1.0f, 0.0f));
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
        proj  = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view");
        unsigned int projLoc  = glGetUniformLocation(ourShader.ID, "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(proj));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    inline void Finish(GLFWwindow* window){
        //----------------------------------------------------------------------
        //Deletando VAO, VBO e EBO para fechar o programa (opcional)
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

};