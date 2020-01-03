#include "glimac/primitives/Primitive.hpp"

namespace glimac {

    /***** OTHERS FUNCTIONS *****/

    const std::vector<ShapeVertexHomo> createQuad(const float &size) {
        glm::vec4 normal(0.f, 0.f, 1.f, 0.f);
        float depth = 0.f;
        float offset = size / 2.f;

        std::vector<ShapeVertexHomo> vertices = {
            ShapeVertexHomo(glm::vec4(-offset, offset, depth, 1), normal, glm::vec2(0, 1)), //Top Left
            ShapeVertexHomo(glm::vec4(-offset, -offset, depth, 1), normal, glm::vec2(0, 0)), //Bottom Left
            ShapeVertexHomo(glm::vec4(offset, offset, depth, 1), normal, glm::vec2(1, 1)), //Top Right
            ShapeVertexHomo(glm::vec4(offset, -offset, depth, 1), normal, glm::vec2(1, 0)) //Bottom Right
        };

        return vertices;
    }

}