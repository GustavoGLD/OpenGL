#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main(){

    #pragma region Configurando janela...

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Rectangle by !Gustavo!", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    #pragma endregion




    #pragma region Vertex Shader

    //Criar objeto para vertexShader. Armazenar ID
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //Colocar o código `vertexShaderSource` ao objeto `vertexShader`
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    //Compilar objeto `vertexShader`
    glCompileShader(vertexShader);

    #pragma endregion



    #pragma region Erro em compilar VertexShader?

    //Booleana do sucesso da compilação
    int sucess;

    //String da info do erro de compilação
    char infoLog[512];

    //Colocar na booleana `sucess` se foi compilado corretamente
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess);

    //Se sucesso for falso..
    if (!sucess){

        //Colocar na String infolog a informação do erro
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);

        //Printar na tela o erro
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    #pragma endregion

    

    #pragma region FragmentShader

    //Criar objeto para fragmentShader. Armazenar ID
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    //Colocar o código `fragmentShaderSource` ao objeto `fragmentShader`
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    //Compilar objeto `fragmentShader`
    glCompileShader(fragmentShader);

    #pragma endregion


    #pragma region Erro ao compilar FragmentShader?

    //Podemos aproivar as variáveis `sucess` e `infoLog[512]` ja existentes

    //Colocar na booleana `secess` se foi compilado corretamente
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &sucess);

    //Se sucesso for falso...
    if (!sucess){

        //Colocar na String infoLog a informação do erro
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);

        //Printar na tela o erro
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;   
    }

    #pragma endregion



    #pragma region shaderProgram

    //Criar shaderProgram
    unsigned int shaderProgram = glCreateProgram();

    //Adicionar o VertexShader ao shaderProgram
    glAttachShader(shaderProgram, vertexShader);

    //Adicionar o FragmentShader ao ShaderProgram
    glAttachShader(shaderProgram, fragmentShader);

    //Linkar os shaders uns aos outros
    glLinkProgram(shaderProgram);

    //Verificar se o programa linkou corretamente em `sucess`
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &sucess);

    //Se o sucesso for falso
    if (!sucess){

        //Pega informações para o `infoLog`
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);

        //Printa o erro na tela
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    #pragma endregion

    //Já criamos o ShaderProgram com o VertexShader e Fragment linkados
    //Não precisamos mais deles. ShaderProgram já tem o que precisa
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    //Todos os vértices que usaremos no retangulo
    float vertices[] = {
         0.5f,  0.5f, 0.0f, //0     //Superior-direito
         0.5f, -0.5f, 0.0f, //1     //Inferior-direito
        -0.5f, -0.5f, 0.0f, //2     //Inferior-esquerdo
        -0.5f,  0.5f, 0.0f, //3     //Superior-esquerdo
    };

    //Os 2 triangulos que serão desenhados para formar o retangulo
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    //Criando e gerando VBO, VAO, EBO
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    //Ligar VAO, ela que administrará os vertices da VBO e EBO
    glBindVertexArray(VAO);

    //Ligando VBO como GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //Passando os vertices para a VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Ligando EBO, ela que armazenará os indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //Passando os indices para a EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Instruindo a VAO a administrar os vertices passados
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Escolar as instruções passadas
    glEnableVertexAttribArray(0);

    //Desligar VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Desligar VAO
    glBindVertexArray(0);

    //A EBO sempre deve ser desligada DEPOIS da VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    //Enquanto o comando de fechar janela nao for acionado
    while (!glfwWindowShouldClose(window))
    {
        //Função de processar Inputs
        processInput(window);

        //Cor de fundo
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        //Limpar tela com a cor de fundo
        glClear(GL_COLOR_BUFFER_BIT);

        //Usar programa de shaders
        glUseProgram(shaderProgram);

        //Ligar VAO criada (opcional, ja nao desligamos antes)
        glBindVertexArray(VAO);

        //Desenhar os elementos
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //Limpar buffers do GLFW
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Desligar VAO, VBO, EBO e ShaderProgram (opcional)
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();

    return 0;
    
}

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}