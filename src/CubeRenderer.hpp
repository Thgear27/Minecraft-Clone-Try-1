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

#define FRONT_FACE 0x20
#define BACK_FACE  0x10
#define RIGHT_FACE 0x08
#define LEFT_FACE  0x04
#define UP_FACE    0x02
#define DOWN_FACE  0x01
#define ALL_FACES  0x3F

struct CubeTextureData {
    float uv_front_x;
    float uv_front_y;
    float uv_back_x;
    float uv_back_y;
    float uv_right_x;
    float uv_right_y;
    float uv_left_x;
    float uv_left_y;
    float uv_up_x;
    float uv_up_y;
    float uv_down_x;
    float uv_down_y;
};

class CubeRenderer {
public:
    enum CubeType {
        GRASS, //
        STONE,
        HORN,
        CRAFTING_TABLE,
        MAX
    };

    enum {
        // VERTICES INDICES
        BACK_FACE_INDEX  = 0,
        FRONT_FACE_INDEX = 6,
        LEFT_FACE_INDEX  = 12,
        RIGHT_FACE_INDEX = 18,
        DOWN_FACE_INDEX  = 24,
        UP_FACE_INDEX    = 30,

        // GRASS
        GRASS_LATERAL_TEX_X = 3,
        GRASS_LATERAL_TEX_Y = 0,
        GRASS_UP_TEX_X      = 9,
        GRASS_UP_TEX_Y      = 9,
        GRASS_DOWN_TEX_X    = 2,
        GRASS_DOWN_TEX_Y    = 0,

        // STONE
        STONE_ALL_TEX_X = 1,
        STONE_ALL_TEX_Y = 0,
    };

private:
    std::array<float, 36 * 5> verticesData;

    VertexArray m_vaos[CubeType::MAX];
    VertexBuffer m_vbos[CubeType::MAX];

    CubeTextureData m_cubesData[CubeType::MAX];

    Texture2D m_cubeTexture; // This texture have all the cubes textures
    ShaderProgram& m_shaderProgram;

    void loadAllCubesVAO();
    void loadCubesTexturesData();

public:
    CubeRenderer(ShaderProgram& programToBeUsed);
    ~CubeRenderer();

    void render(const glm::vec3& position, CubeType type, u_int8_t faces);
};

#endif // __CUBERENDERER_H__