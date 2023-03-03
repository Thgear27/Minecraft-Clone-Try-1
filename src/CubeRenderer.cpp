#include "CubeRenderer.hpp"

CubeRenderer::CubeRenderer(ShaderProgram& programToBeUsed)
    : m_shaderProgram(programToBeUsed) {
    verticesData = {
        // BACK FACE
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, //
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, //
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, //
        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, //
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, //

        // FRONT FACE
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, //
        -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, //
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, //
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, //
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, //
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, //

        // LEFT FACE
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
        -0.5f, 0.5f,  -0.5f, 0.0f, 0.0f, //
        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, //
        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, //
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //

        // RIGHT FACE
        0.5f,  0.5f, -0.5f, 1.0f, 0.0f, //
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, //
        0.5f, -0.5f,  0.5f, 0.0f, 1.0f, //
        0.5f, -0.5f,  0.5f, 0.0f, 1.0f, //
        0.5f,  0.5f,  0.5f, 0.0f, 0.0f, //
        0.5f,  0.5f, -0.5f, 1.0f, 0.0f, //

        // DOWN FACE
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, //
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, //
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, //
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //

        // UP FACE
        -0.5f, 0.5f,  0.5f, 0.0f, 1.0f, //
         0.5f, 0.5f,  0.5f, 1.0f, 1.0f, //
         0.5f, 0.5f, -0.5f, 1.0f, 0.0f, //
         0.5f, 0.5f, -0.5f, 1.0f, 0.0f, //
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, //
        -0.5f, 0.5f,  0.5f, 0.0f, 1.0f  //
    };

    m_cubeTexture.loadImageData("resources/img/sdlLogo.png", 0, GL_RGBA, GL_RGBA);
    m_cubeTexture.setTextureUnit(0);

    m_vbo.loadData(sizeof(verticesData), verticesData.begin(), GL_STATIC_DRAW);
    m_vbo.push_VertexAttribLayout(GL_FLOAT, GL_FALSE, 3);
    m_vbo.push_VertexAttribLayout(GL_FLOAT, GL_FALSE, 2);

    m_vao.addVertexBuffer(&m_vbo);
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
