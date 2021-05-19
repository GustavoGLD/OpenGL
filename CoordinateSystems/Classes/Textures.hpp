#include "../Libs/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../Libs/stb_image.h"

class Textures{
public:
    unsigned int texture;

    inline void SettingUpTextures(){
        SettingUpFilter();
        SettingUpImage();
    }

private:
    inline void SettingUpFilter(){

        //-------------------------------------------
        //Definindo, gerando, e ligando a Textura
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        //------------------------------------
        //Definindo o Wrapping da Textura
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        //-----------------------------------------------------------
        //Definindo o Filtro da Textura (pontual, bilinear, etc)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    }

    inline void SettingUpImage(){

        //-----------------------------------------------------------------------
        //Carregando a Imagem em *data, guardando Informações e tratando erros
        int width, height, nrChannels;
        unsigned char *data = stbi_load("Classes/Images/container.jpg", &width, &height, &nrChannels, 0);
        if (data) {

            //-------------------------------------------------------------------
            //Gerando a Textura com a Imagem carregada
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

            //-------------------------------------------------------------------
            //Gerando MipMaps 
            glGenerateMipmap(GL_TEXTURE_2D);

        }
        else { std::cout << "Failed to load texture" << std::endl; }

        //-----------------------------------------------------------
        //Apagar o data* com a imagem, depois de criada a textura
        stbi_image_free(data);
    }
};