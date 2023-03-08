#include "CubeRenderer.hpp"

CubeRenderer::CubeRenderer(ShaderProgram& programToBeUsed)
    : m_shaderProgram(programToBeUsed) {

    m_cubeTexture.loadImageData("resources/img/texturesv4.png", 0, GL_RGBA, GL_RGBA);
    m_cubeTexture.setTextureUnit(0);

    loadCubesTexturesData();
    loadAllCubesVAO();
}

CubeRenderer::~CubeRenderer() {}

void CubeRenderer::render(const glm::vec3& position, CubeType type, u_int8_t faces) {
    glm::mat4 model = glm::mat4 { 1.0f };
    model           = glm::translate(model, position);

    m_shaderProgram.setMat4("model", model);

    m_vaos[type].bind();
    // GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
    if (faces & BACK_FACE) {
        GLCall(glDrawArrays(GL_TRIANGLES, BACK_FACE_INDEX, 6));
    }
    if (faces & FRONT_FACE) {
        GLCall(glDrawArrays(GL_TRIANGLES, FRONT_FACE_INDEX, 6));
    }
    if (faces & LEFT_FACE) {
        GLCall(glDrawArrays(GL_TRIANGLES, LEFT_FACE_INDEX, 6));
    }
    if (faces & RIGHT_FACE) {
        GLCall(glDrawArrays(GL_TRIANGLES, RIGHT_FACE_INDEX, 6));
    }
    if (faces & UP_FACE) {
        GLCall(glDrawArrays(GL_TRIANGLES, UP_FACE_INDEX, 6));
    }
    if (faces & DOWN_FACE) {
        GLCall(glDrawArrays(GL_TRIANGLES, DOWN_FACE_INDEX, 6));
    }
    m_vaos[type].unBind();
}

void CubeRenderer::loadAllCubesVAO() {
    // Cargar los vaos y vbos
    for (int i = 0; i < CubeType::MAX; i++) {
        float x_front = m_cubesData[i].uv_front_x;
        float y_front = m_cubesData[i].uv_front_y;
        float x_back  = m_cubesData[i].uv_back_x;
        float y_back  = m_cubesData[i].uv_back_y;
        float x_right = m_cubesData[i].uv_right_x;
        float y_right = m_cubesData[i].uv_right_y;
        float x_left  = m_cubesData[i].uv_left_x;
        float y_left  = m_cubesData[i].uv_left_y;
        float x_up    = m_cubesData[i].uv_up_x;
        float y_up    = m_cubesData[i].uv_up_y;
        float x_down  = m_cubesData[i].uv_down_x;
        float y_down  = m_cubesData[i].uv_down_y;

        float xn_front = (x_front + 1) / 16.0f;
        float yn_front = (y_front + 1) / 16.0f;
        x_front /= 16.0f;
        y_front /= 16.0f;
        float xn_back = (x_back + 1) / 16.0f;
        float yn_back = (y_back + 1) / 16.0f;
        x_back /= 16.0f;
        y_back /= 16.0f;
        float xn_right = (x_right + 1) / 16.0f;
        float yn_right = (y_right + 1) / 16.0f;
        x_right /= 16.0f;
        y_right /= 16.0f;
        float xn_left = (x_left + 1) / 16.0f;
        float yn_left = (y_left + 1) / 16.0f;
        x_left /= 16.0f;
        y_left /= 16.0f;
        float xn_up = (x_up + 1) / 16.0f;
        float yn_up = (y_up + 1) / 16.0f;
        x_up /= 16.0f;
        y_up /= 16.0f;
        float xn_down = (x_down + 1) / 16.0f;
        float yn_down = (y_down + 1) / 16.0f;
        x_down /= 16.0f;
        y_down /= 16.0f;

        verticesData = {
            // BACK FACE
            -0.5f, -0.5f, -0.5f, xn_back, yn_back, //
            0.5f, -0.5f, -0.5f, x_back, yn_back,   //
            0.5f, 0.5f, -0.5f, x_back, y_back,     //
            0.5f, 0.5f, -0.5f, x_back, y_back,     //
            -0.5f, 0.5f, -0.5f, xn_back, y_back,   //
            -0.5f, -0.5f, -0.5f, xn_back, yn_back, //

            // FRONT FACE
            0.5f, -0.5f, 0.5f, xn_front, yn_front, //
            -0.5f, -0.5f, 0.5f, x_front, yn_front, //
            -0.5f, 0.5f, 0.5f, x_front, y_front,   //
            -0.5f, 0.5f, 0.5f, x_front, y_front,   //
            0.5f, 0.5f, 0.5f, xn_front, y_front,   //
            0.5f, -0.5f, 0.5f, xn_front, yn_front, //

            // LEFT FACE
            -0.5f, -0.5f, -0.5f, x_left, yn_left, //
            -0.5f, 0.5f, -0.5f, x_left, y_left,   //
            -0.5f, 0.5f, 0.5f, xn_left, y_left,   //
            -0.5f, 0.5f, 0.5f, xn_left, y_left,   //
            -0.5f, -0.5f, 0.5f, xn_left, yn_left, //
            -0.5f, -0.5f, -0.5f, x_left, yn_left, //

            // RIGHT FACE
            0.5f, 0.5f, -0.5f, xn_right, y_right,   //
            0.5f, -0.5f, -0.5f, xn_right, yn_right, //
            0.5f, -0.5f, 0.5f, x_right, yn_right,   //
            0.5f, -0.5f, 0.5f, x_right, yn_right,   //
            0.5f, 0.5f, 0.5f, x_right, y_right,     //
            0.5f, 0.5f, -0.5f, xn_right, y_right,   //

            // DOWN FACE
            -0.5f, -0.5f, -0.5f, x_down, yn_down, //
            0.5f, -0.5f, -0.5f, xn_down, yn_down, //
            0.5f, -0.5f, 0.5f, xn_down, y_down,   //
            0.5f, -0.5f, 0.5f, xn_down, y_down,   //
            -0.5f, -0.5f, 0.5f, x_down, y_down,   //
            -0.5f, -0.5f, -0.5f, x_down, yn_down, //

            // UP FACE
            -0.5f, 0.5f, 0.5f, x_up, yn_up, //
            0.5f, 0.5f, 0.5f, xn_up, yn_up, //
            0.5f, 0.5f, -0.5f, xn_up, y_up, //
            0.5f, 0.5f, -0.5f, xn_up, y_up, //
            -0.5f, 0.5f, -0.5f, x_up, y_up, //
            -0.5f, 0.5f, 0.5f, x_up, yn_up  //
        };

        m_vbos[i].loadData(sizeof(verticesData), verticesData.begin(), GL_STATIC_DRAW);
        m_vbos[i].push_VertexAttribLayout(GL_FLOAT, GL_FALSE, 3);
        m_vbos[i].push_VertexAttribLayout(GL_FLOAT, GL_FALSE, 2);

        m_vaos[i].addVertexBuffer(&m_vbos[i]);
        m_vaos[i].linkBuffers();
    }
}

void CubeRenderer::loadCubesTexturesData() {
    for (int i = 0; i < CubeType::MAX; i++) {
        if (i == CubeType::GRASS) {
            m_cubesData[i].uv_front_x = GRASS_LATERAL_TEX_X;
            m_cubesData[i].uv_front_y = GRASS_LATERAL_TEX_Y;
            m_cubesData[i].uv_back_x  = GRASS_LATERAL_TEX_X;
            m_cubesData[i].uv_back_y  = GRASS_LATERAL_TEX_Y;
            m_cubesData[i].uv_left_x  = GRASS_LATERAL_TEX_X;
            m_cubesData[i].uv_left_y  = GRASS_LATERAL_TEX_Y;
            m_cubesData[i].uv_right_x = GRASS_LATERAL_TEX_X;
            m_cubesData[i].uv_right_y = GRASS_LATERAL_TEX_Y;
            m_cubesData[i].uv_up_x    = GRASS_UP_TEX_X;
            m_cubesData[i].uv_up_y    = GRASS_UP_TEX_Y;
            m_cubesData[i].uv_down_x  = GRASS_DOWN_TEX_X;
            m_cubesData[i].uv_down_y  = GRASS_DOWN_TEX_Y;
        } else if (i == CubeType::STONE) {
            m_cubesData[i].uv_front_x = STONE_ALL_TEX_X;
            m_cubesData[i].uv_front_y = STONE_ALL_TEX_Y;
            m_cubesData[i].uv_back_x  = STONE_ALL_TEX_X;
            m_cubesData[i].uv_back_y  = STONE_ALL_TEX_Y;
            m_cubesData[i].uv_left_x  = STONE_ALL_TEX_X;
            m_cubesData[i].uv_left_y  = STONE_ALL_TEX_Y;
            m_cubesData[i].uv_right_x = STONE_ALL_TEX_X;
            m_cubesData[i].uv_right_y = STONE_ALL_TEX_Y;
            m_cubesData[i].uv_up_x    = STONE_ALL_TEX_X;
            m_cubesData[i].uv_up_y    = STONE_ALL_TEX_Y;
            m_cubesData[i].uv_down_x  = STONE_ALL_TEX_X;
            m_cubesData[i].uv_down_y  = STONE_ALL_TEX_Y;
        } else {
            m_cubesData[i].uv_front_x = 10;
            m_cubesData[i].uv_front_y = 10;
            m_cubesData[i].uv_back_x  = 10;
            m_cubesData[i].uv_back_y  = 10;
            m_cubesData[i].uv_left_x  = 10;
            m_cubesData[i].uv_left_y  = 10;
            m_cubesData[i].uv_right_x = 10;
            m_cubesData[i].uv_right_y = 10;
            m_cubesData[i].uv_up_x    = 10;
            m_cubesData[i].uv_up_y    = 10;
            m_cubesData[i].uv_down_x  = 10;
            m_cubesData[i].uv_down_y  = 10;
        }
    }
}