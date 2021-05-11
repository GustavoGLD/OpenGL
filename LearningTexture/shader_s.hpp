//===============================================================================
// *** Esse Header será responsável por tudo que é referente as Shaders. ***
// *** Desde lê-las até linkar ao Shader Program                         ***
//===============================================================================

//-------------------------------------------------------------------------------
//Sistema para evitar que esse header seja lido novamente
#ifndef SHADER_S
#define SHADER_S

//-------------------------------------------------------------------------------
//Inclusões
#include "glad/glad.h"
#include "glm/glm.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
public:

    //---------------------------------------------------------------------------
    //O ID do nosso programa de Shaders
    unsigned int ID;

    //---------------------------------------------------------------------------
    //Construtor que irá abrir, ler e compilar shader
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr){

        //-----------------------------------------------------------------------
        //Shader em formato de string
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode; //isso pode ta sendo declarado atoa

        //-----------------------------------------------------------------------
        //Shader em formato de arquivo
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;

        //-----------------------------------------------------------------------
        //Para ter certeza da captação de erro com a leitura das shaders
        //Failbit é erro de lógico. Badbit erro de integridade
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

        try 
        {
            //-------------------------------------------------------------------
            //Abrir arquivos com os diretórios dado
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);


            //-------------------------------------------------------------------
            //Lendo os arquivos e passando para  variaveis StringStream
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();		
            
            //-------------------------------------------------------------------
            //Ja podemos fechar os arquivos, depois de lidos
            vShaderFile.close();
            fShaderFile.close();

            //-/-----------------------------------------------------------------
            //Convertendo Stringstream para String
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();			
            // if geometry shader path is present, also load a geometry shader
            if(geometryPath != nullptr)
            {
                gShaderFile.open(geometryPath);
                std::stringstream gShaderStream;
                gShaderStream << gShaderFile.rdbuf();
                gShaderFile.close();
                geometryCode = gShaderStream.str();
            }
        }

        //---------------------------------------------------------------------
        //Caso algum erro tenha acontecido
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        
        //---------------------------------------------------------------------
        //Converte de string para const char*
        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();


        //---------------------------------------------------------------------
        //Criar, compilar e checar erros da Vertex Shader
        GLint success; GLchar infoLog[1024];
        unsigned int vertex, fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        checkCompileErrors(vertex, "VERTEX");
        
        //---------------------------------------------------------------------
        //Criar, compilar e checar erros da Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        checkCompileErrors(fragment, "FRAGMENT");

        //---------------------------------------------------------------------
        //Criar, compilar e checar erros da Geometry Shader (Caso houver)
        unsigned int geometry;
        if(geometryPath != nullptr)
        {
            const char * gShaderCode = geometryCode.c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, NULL);
            glCompileShader(geometry);
            glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
            checkCompileErrors(geometry, "GEOMETRY");
        }
        
        //---------------------------------------------------------------------
        //Criar, linkar e checkar erros no Shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        if(geometryPath != nullptr)
        glAttachShader(ID, geometry);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        
        //---------------------------------------------------------------------
        //Excluir Shaders, após linkadas ao programa
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if(geometryPath != nullptr)
        glDeleteShader(geometry);
    }

    //-------------------------
    //Usar Shader Program
    void use() 
    { 
        glUseProgram(ID); 
    }

    //-------------------------------------------------------------------------
    //Setar um uniforme da Shader Program
    void setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const
    { 
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setVec2(const std::string &name, float x, float y) const
    { 
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    { 
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const
    { 
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setVec4(const std::string &name, float x, float y, float z, float w) 
    { 
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:

    // Método que irá Checkar erros em algum objeto, seja Shader ou Program
    // @param object  [Passar a Shader/Program que será analisado]
    // @param type    ["VERTEX", "FRAGMENT", "GEOMETRY" ou "PROGRAM"]
    // @return vazio
    void checkCompileErrors(GLuint object, std::string type)
    {   

        //-----------------------------------------------
        //Sucess terá o código do erro, e 0 não houver
        GLint success;

        //----------------------------------------
        //infoLog guardará a mensagem de erro
        GLchar infoLog[1024];

        //-------------------------------
        //Se o Type for do "PROGRAM"
        if(type != "PROGRAM")
        {
            
            //-----------------------------------
            //Guardar o código do erro em Sucess
            glGetShaderiv(object, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(object, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog 
                << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }


        else
        {
            glGetProgramiv(object, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(object, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog 
                << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};

#endif