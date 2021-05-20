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
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    float deltaTime, time;

public:
    inline void Start(GLFWwindow* window){
        ourShader.newShader("Classes/Shaders/vertexShader.vs", "Classes/Shaders/fragmentShader.fs");
        SettingUpBuffers();
        SettingUpTextures();
        glEnable(GL_DEPTH_TEST);
        cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
        cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    }

    inline void Update(GLFWwindow* window){

        glBindTexture(GL_TEXTURE_2D, texture);
        glUseProgram(ourShader.ID);
        glBindVertexArray(VAO);
        RenderOurCubes(ourShader, window, cubePositions);
    }

    inline void Finish(GLFWwindow* window){
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    inline void RenderOurCubes(Shader ourShader, GLFWwindow* window, glm::vec3 cubePositions[]){
        deltaTime = glfwGetTime() - time;
        time = glfwGetTime();
        std::cout << 1 / deltaTime << std::endl;
        
        const float cameraSpeed = 5.0f;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;

        glm::mat4 view  = glm::mat4(1.0f);
        view  = glm::lookAt(cameraPos, cameraPos + cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
        unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view");
        glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(view));

        //std::cout << cameraPos[0] << "\t" << cameraPos[1] << "\t" << cameraPos[2] << "\n\n";

        glm::mat4 proj  = glm::mat4(1.0f);
        int width, height; glfwGetWindowSize(window, &width, &height);
        proj  = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        unsigned int projLoc  = glGetUniformLocation(ourShader.ID, "projection");
        glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(proj));

        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }

};