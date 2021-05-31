#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Triangle by !Gustavo!", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    #pragma endregion


    #pragma region VertexShader

    //Criar objeto para vertexSharde. Armazenar ID
    unsigned int vertexSharder = glCreateShader(GL_VERTEX_SHADER);

    //Colocar o código `vertexShaderSource` ao objeto `vertexSharder`
    glShaderSource(vertexSharder, 1, &vertexShaderSource, NULL);

    //Compilar objeto `vertexShader`
    glCompileShader(vertexSharder);

    #pragma endregion




    #pragma region Erro em compilar VertexShader?

    //Booleana do sucesso da compilação
    int sucess;

    //String da info do erro de compilação 
    char infoLog[512];

    //Colocar na booleana `secess` se foi compilado corretamente
    glGetShaderiv(vertexSharder, GL_COMPILE_STATUS, &sucess);

    //Se sucesso for falso...
    if (!sucess){

        //Colocar na String infoLog a informação do erro
        glGetShaderInfoLog(vertexSharder, 512, NULL, infoLog);

        //Printar na tela o erro
        std::cout << "ERROR::SHADER::VERTEX::COMPULATION_FAILED\n" << infoLog << std::endl;
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
        std::cout << "ERROR::SHADER::FRAGMENT::COMPULATION_FAILED\n" << infoLog << std::endl;
    }

    #pragma endregion




    #pragma region shaderProgram

    //Criar shaderProgram
    unsigned int shaderProgram = glCreateProgram();

    //Adicionar o VertexShader ao shaderProgram
    glAttachShader(shaderProgram, vertexSharder);

    //Adicionar o FragmentShader ao ShaderProgram
    glAttachShader(shaderProgram, fragmentShader);

    //Linkar os shaders uns aos outros
    glLinkProgram(shaderProgram);

    #pragma endregion



    //Já criamos o ShaderProgram com o VertexShader e Fragment linkados
    //Não precisamos mais deles. ShaderProgram já tem o que precisa
    glDeleteShader(vertexSharder);
    glDeleteShader(fragmentShader);



    #pragma region Vertex Buffer Object e Vertex Array Object 

    //Coordenadas dos vértices do triângulo
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // esquerda
         0.5f, -0.5f, 0.0f, // direita
         0.0f,  0.5f, 0.0f, // cima
    };

    //Criando objeto para o VBO e VAO
    unsigned int VBO, VAO;

    //Gerando VBO e VAO com os objetos declarados acima. Recebendo ID
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //Ligar o VAO. Ele quem administra a VBO e os vértices
    glBindVertexArray(VAO);

    //Ligar VBO como um Buffer de Array. Ele quem armazena os vértices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //Passar o array de vertices criado para nosso VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Instruindo como o VAO deve administrar esses vértices passados
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Usar a instrução dada acima
    glEnableVertexAttribArray(0);

    //Desvincular VBO para evitar ser modificado
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Desvincular VAO para evitar ser modificado
    glBindVertexArray(0);

    #pragma endregion




    //Enquanto a janela não está programada para fechar
    while (!glfwWindowShouldClose(window)){

        //Input
        processInput(window);

        //Definir cor de fundo
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        //Limpar tela para a cor de fundo definida
        glClear(GL_COLOR_BUFFER_BIT);




        //Usar programa criado anteriormente
        glUseProgram(shaderProgram);

        //Vinculando VAO
        glBindVertexArray(VAO);

        //Desenhando triângulo com o array no VAO.
        glDrawArrays(GL_TRIANGLES, 0, 3);


        //Limpando buffers do GLFW.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Excluindo VAO.
    glDeleteVertexArrays(1, &VAO);
    //Excluindo VBO.
    glDeleteBuffers(1, &VBO);
    //Exlcuindo Program.
    glDeleteProgram(shaderProgram);

    //Finalizando GLFW.
    glfwTerminate();
    return 0;

}

//Função para pegar Inputs.
void processInput(GLFWwindow *window){

    //Se o botão de fechar for clidado.
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){

        // programamos a janela para fechar.
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}
