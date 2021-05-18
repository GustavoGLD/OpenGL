#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../Libs/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "Main.hpp"

class Window : public Main {
private:
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    GLFWwindow* window;

public:
    inline void CreateWindow(){

        SettingUpWindow();
        OpenWindow();
        SettingUpGLAD();
        Start();
    }

    inline void RenderingLoop(){
        while(true){
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                break;
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            Update();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    inline void DestroyWindow(){
        
        //----------------------------------------------------------------------
        //Fechando o GLFW e finalizando o programa
        Finish();
        glfwTerminate();
    } 

private:
    inline void SettingUpWindow(){

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
    }


    inline void OpenWindow(){

        //-------------------------------------------------------------------
        //Criando Janela, tratando erros e criando contexto com a janela
        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    }


    inline void SettingUpGLAD(){

        //-----------------------------------------------------------------
        //Ligando e configurando o GLAD de acordo o Sistema Operacional
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
    }

    inline static void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window, true);
            std::cout << "Fecha aí" << std::endl;
        }
    }

    inline static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
};

#endif