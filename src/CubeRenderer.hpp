#ifndef __CUBERENDERER_H__
#define __CUBERENDERER_H__

#include "OpenGL/Buffers/ElementBuffer.hpp"
#include "OpenGL/Buffers/VertexArray.hpp"
#include "OpenGL/Buffers/VertexBuffer.hpp"
#include "OpenGL/GLerror.hpp"
#include "OpenGL/ShaderProgram.hpp"
#include "OpenGL/Texture2D.hpp"
#include <array>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CubeRenderer {
private:
    std::array<float, 36 * 5> verticesData;
    // std::array<GLuint, 36> indicesData;
    VertexBuffer m_vbo;
    VertexArray m_vao;

    Texture2D m_cubeTexture; // This texture have all the cubes textures
    ShaderProgram& m_shaderProgram;

public:
    CubeRenderer(ShaderProgram& programToBeUsed);
    ~CubeRenderer();

    void render(const glm::vec3& position);
};

#endif // __CUBERENDERER_H__