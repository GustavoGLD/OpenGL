#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include<iostream>
#include<cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
    "}\n\0";

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FlashingTriangle by !Gustavo!", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int sucess;
    char infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess);
    if (!sucess){
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &sucess);
    if (!sucess){
        glGetProgramInfoLog(fragmentShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
    }
    
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &sucess);
    if (!sucess){
        glGetShaderInfoLog(shaderProgram, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::PR::COMPILATION_FAILED\n" << infolog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
        //Triangulo inferior esquerdo
        -0.9f, -0.9f, 0.0f, //inferior esquerdo
        -0.1f, -0.9f, 0.0f, //inferior direito
        -0.5f, -0.1f, 0.0f, //superior

        //Triangulo inferior direito
        0.1f, -0.9f, 0.0f,  //inferior esquerdo
        0.9f, -0.9f, 0.0f,  //inferior direito
        0.5f, -0.1f, 0.0f,  //superior

        //Triangulo superior
        -0.4f, 0.1f, 0.0f, //inferior esquerdo
         0.4f, 0.1f, 0.0f, //inferior direito
         0.0f, 0.9f, 0.0f,  //superior

        //Triangulo central
        -0.4f,  0.0f, 0.0f, //superior esquerdo
         0.4f,  0.0f, 0.0f, //superior direito
         0.0f, -0.8f, 0.0f //inferior
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        //Fazer a intensidade variar de 0 a 1 de acordo o tempo de execução
        float intensity = sin(glfwGetTime() * 5) / 2 + 0.5f;

        //Pegar ID do local da nossa input da vertexShader "ourColor"
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

        //glUniform4f defini a cor do triangulo
        //glDrawArray desenha o triângulo

        glUniform4f(vertexColorLocation, intensity, 0.0f, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUniform4f(vertexColorLocation, 0.0f, intensity, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 3, 3);

        glUniform4f(vertexColorLocation, 0.0f, 0.0f, intensity, 1.0f);
        glDrawArrays(GL_TRIANGLES, 6, 3);

        glUniform4f(vertexColorLocation, intensity, intensity, intensity, 1.0f);
        glDrawArrays(GL_TRIANGLES, 9, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}