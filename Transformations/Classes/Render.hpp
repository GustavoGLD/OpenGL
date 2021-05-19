#ifndef RENDER_HPP
#define RENDER_HPP

#include "../Libs/glad/glad.h"
#include "../Libs/glm/glm.hpp"
#include "../Libs/glm/gtc/matrix_transform.hpp"
#include "../Libs/glm/gtc/type_ptr.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

#include "../Classes/Buffers.hpp"
#include "../Classes/Textures.hpp"
#include "../Classes/Render.hpp"

class Render {
public:

    inline void RenderOurImage(Shader ourShader, int VAO, int directX, int directY){
        float a = sinf(glfwGetTime()) / 2 + 0.5f;
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3((a - 0.5) * directX, (a - 0.5) * directY, 0));
        trans = glm::rotate(trans, glm::radians(360 * a), glm::vec3(0.0, 0.0, 0.1));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        ourShader.use();
        GLuint transLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
};

#endif