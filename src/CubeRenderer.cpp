#include "CubeRenderer.hpp"

CubeRenderer::CubeRenderer(ShaderProgram& programToBeUsed)
    : m_shaderProgram(programToBeUsed) {
    verticesData = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //
        0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, //
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //

        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //
        -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, //
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //

        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, //
        -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, //

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, //
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, //
        0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, //
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
        0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, //
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //

        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
        -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, //
        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f  //
    };

    uint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    m_cubeTexture.loadImageData("resources/img/textures.png", 0, GL_RGBA, GL_RGBA);
    m_cubeTexture.setTextureUnit(0);

    m_vbo.loadData(sizeof(verticesData), verticesData.begin(), GL_STATIC_DRAW);
    m_vbo.push_VertexAttribLayout(GL_FLOAT, GL_FALSE, 3);
    m_vbo.push_VertexAttribLayout(GL_FLOAT, GL_FALSE, 2);

    m_ebo.loadData(sizeof(indices), indices, GL_STATIC_DRAW);

    m_vao.addVertexBuffer(&m_vbo);
    m_vao.addElementBuffer(&m_ebo);
    m_vao.linkBuffers();
}

CubeRenderer::~CubeRenderer() {}

void CubeRenderer::render(const glm::vec3& position) {
    glm::mat4 model = glm::mat4 { 1.0f };
    model           = glm::translate(model, position);

    m_shaderProgram.setMat4("model", model);

    m_vao.bind();
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
    m_vao.unBind();
}
