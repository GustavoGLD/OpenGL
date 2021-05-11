//---------------------------------------------
//Esse código lerá e compilará nossas shaders
//---------------------------------------------


//----------------------------------------------
//Sistema para esse header não ser lido 2 vezes
#ifndef SHADER_H
#define SHADER_H

//--------------------
//incluir bibliotecas
#include "glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//--------------
//Classe Shader
class Shader{
public:
    //Criando um ID para nosso ShaderProgram.
    unsigned int ID;

    //Criando um construtor para ler e compilar as shaders.
    Shader(const char* vertexPath, const char* fragmentPath){

        //------------------------------------------------
        #pragma region abrindo e lendo código das shaders

        //Shader em forma de string.
        std::string vertexCode;
        std::string fragmentCode;

        //Shader em forma de arquivo.
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        //Para termos certeza da captação de erros,
        //caso houver entre as shaders e o ifstream.
        //Failbit: erros de lógica. Badbit: erros de integridade
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try{

            //Abrir arquivos com as shaders, no diretório dito
            //no parametro do construtor
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);

            //Shader em forma de stringstream
            std::stringstream vShaderStream;
            std::stringstream fShaderStream;
            
            //Lendo as shaders e passando para stringstreams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            //Convertendo as stringstreams em strings
            vertexCode   = vShaderStream.str();
            fragmentCode = fShaderStream.str();
            
            //Fechando arquivos
            vShaderFile.close();
            fShaderFile.close();

        }

        //Caso algum erro com os arquivos tenha acontecido
        catch(std::ifstream::failure e){

            std::cout << "ERROR::SHADER::FILE_NOT_SUCESSFULLY_READ" << std::endl;

        }

        //Agora finalmente transformando as shaders de string para const char*
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        #pragma endregion
        //------------------------------------------------
        

        //----------------------------------------------------
        //Criando as Shaders com o código obtido e compilando.
        //Criando um programa com essas shaders, e linkando.
        #pragma region compilando shaders / criando programa

        unsigned vertex, fragment;
        int success;
        char infolog[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success){
            glGetShaderInfoLog(vertex, 512, NULL, infolog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl;
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success){
            glGetShaderInfoLog(fragment, 512, NULL, infolog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << std::endl;
        }

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success){
            glGetProgramInfoLog(ID, 512, NULL, infolog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        #pragma endregion
        //----------------------------------------------------
    }

    //Metodo para ligar/desligar shader
    void use(){
        glUseProgram(ID);
    }

    //--------------------------------------------------------
    //Funções para definir Uniformes (variaveis do GLSL)
    #pragma region definir Uniformes
    void setBool (const std::string &name,  bool value) const{
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void setInt  (const std::string &name,   int value) const{
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat(const std::string &name, float value) const{
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    #pragma endregion
    //--------------------------------------------------------
};

#endif