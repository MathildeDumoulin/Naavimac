#include "glimac/primitives/Primitive.hpp"

namespace glimac {

    /***** OTHERS FUNCTIONS *****/

    const std::vector<ShapeVertexHomo> createQuad(const float &size) {
        glm::vec2 texture(0.f, 0.f);
        glm::vec4 normal(0.f, 0.f, 1.f, 0.f);
        float depth = 0.f;
        float offset = size / 2.f;

        std::vector<ShapeVertexHomo> vertices = {
            ShapeVertexHomo(glm::vec4(-offset, offset, depth, 1), normal, texture), //Top Left
            ShapeVertexHomo(glm::vec4(-offset, -offset, depth, 1), normal, texture), //Bottom Left
            ShapeVertexHomo(glm::vec4(offset, offset, depth, 1), normal, texture), //Top Right
            ShapeVertexHomo(glm::vec4(offset, -offset, depth, 1), normal, texture) //Bottom Right
        };

        return vertices;
    }

}