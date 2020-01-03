#include "glimac/common/math.hpp"

glm::vec3 roundCoords(const glm::vec3& vec) {
    glm::vec3 rounded = glm::vec3(
        (vec.x >= 0) ? floor(vec.x + 0.5) : ceil(vec.x - 0.5),
        (vec.y >= 0) ? floor(vec.y + 0.5) : ceil(vec.y - 0.5),
        (vec.z >= 0) ? floor(vec.z + 0.5) : ceil(vec.z - 0.5)
    );

    return rounded;
}

glm::vec3 dominantAxis(const glm::vec3& vec) {
    glm::vec3 dominantVec(0, 0, 0);

    //x dominant
    if(abs(vec.x) > abs(vec.y) && abs(vec.x) > abs(vec.z)) {
        dominantVec = glm::vec3(1, 0, 0);
        if(vec.x <= 0) dominantVec = -dominantVec;
    }
    //y dominant
    if(abs(vec.y) > abs(vec.x) && abs(vec.y) > abs(vec.z)) {
        dominantVec = glm::vec3(0, 1, 0);
        if(vec.y <= 0) dominantVec = -dominantVec;
    }
    //z dominant
    if(abs(vec.z) > abs(vec.x) && abs(vec.z) > abs(vec.y)) {
        dominantVec = glm::vec3(0, 0, 1);
        if(vec.z <= 0) dominantVec = -dominantVec;
    }

    return dominantVec;
}