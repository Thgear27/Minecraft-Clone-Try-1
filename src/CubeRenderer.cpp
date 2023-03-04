#include "CubeRenderer.hpp"

CubeRenderer::CubeRenderer(ShaderProgram& programToBeUsed)
    : m_shaderProgram(programToBeUsed) {
    float x = 1;
    float y = 1;

    float xx = (x + 1) / 16.0f;
    float yy = (y + 1) / 16.0f;
    x /= 16.0f;
    y /= 16.0f;

    verticesData = {
        // BACK FACE
        -0.5f, -0.5f, -0.5f, xx, yy, //
         0.5f, -0.5f, -0.5f, x, yy, //
         0.5f,  0.5f, -0.5f, x, y, //
         0.5f,  0.5f, -0.5f, x, y, //
        -0.5f,  0.5f, -0.5f, xx, y, //
        -0.5f, -0.5f, -0.5f, xx, yy, //

        // FRONT FACE
         0.5f, -0.5f,  0.5f, xx, yy, //
        -0.5f, -0.5f,  0.5f, x, yy, //
        -0.5f,  0.5f,  0.5f, x, y, //
        -0.5f,  0.5f,  0.5f, x, y, //
         0.5f,  0.5f,  0.5f, xx, y, //
         0.5f, -0.5f,  0.5f, xx, yy, //

        // LEFT FACE
        -0.5f, -0.5f, -0.5f, x, yy, //
        -0.5f,  0.5f, -0.5f, x, y, //
        -0.5f,  0.5f,  0.5f, xx, y, //
        -0.5f,  0.5f,  0.5f, xx, y, //
        -0.5f, -0.5f,  0.5f, xx, yy, //
        -0.5f, -0.5f, -0.5f, x, yy, //

        // RIGHT FACE
        0.5f,  0.5f, -0.5f, xx, y, //
        0.5f, -0.5f, -0.5f, xx, yy, //
        0.5f, -0.5f,  0.5f, x, yy, //
        0.5f, -0.5f,  0.5f, x, yy, //
        0.5f,  0.5f,  0.5f, x, y, //
        0.5f,  0.5f, -0.5f, xx, y, //

        // DOWN FACE
        -0.5f, -0.5f, -0.5f, x, yy, //
         0.5f, -0.5f, -0.5f, xx, yy, //
         0.5f, -0.5f,  0.5f, xx, y, //
         0.5f, -0.5f,  0.5f, xx, y, //
        -0.5f, -0.5f,  0.5f, x, y, //
        -0.5f, -0.5f, -0.5f, x, yy, //

        // UP FACE
        -0.5f, 0.5f,  0.5f, x, yy, //
         0.5f, 0.5f,  0.5f, xx, yy, //
         0.5f, 0.5f, -0.5f, xx, y, //
         0.5f, 0.5f, -0.5f, xx, y, //
        -0.5f, 0.5f, -0.5f, x, y, //
        -0.5f, 0.5f,  0.5f, x, yy  //
    };

    m_cubeTexture.loadImageData("resources/img/texturesv2.png", 0, GL_RGBA, GL_RGBA);
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
