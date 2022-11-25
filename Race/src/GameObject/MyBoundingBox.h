#ifndef RAYLIB_CPP_EXAMPLE_MYBOUNDINGBOX_H
#define RAYLIB_CPP_EXAMPLE_MYBOUNDINGBOX_H

#include "raylib-cpp.hpp"
#include "raylib.h"
#include <cmath>

class MyBoundingBox
{
public:
    MyBoundingBox(std::vector<float> _min_matrix, float _width, float _height, float _breadth);
    std::vector<float> matAdd(std::vector<float> matrix_1, std::vector<float> matrix_2);
    std::vector<float> matMul(std::vector<float> matrix_1, std::vector<float> matrix_2);
    void rotate(float yaw, float pitch, float roll);
    BoundingBox matToBox(std::vector<float> _min_matrix, std::vector<float> _max_matrix);
    void render();

protected:

private:
    std::vector<float> rotateX(std::vector<float> matrix, float angle_deg);
    std::vector<float> rotateY(std::vector<float> matrix, float angle_deg);
    std::vector<float> rotateZ(std::vector<float> matrix, float angle_deg);
    std::vector<float> generalRotation(std::vector<float> matrix, float yaw, float pitch, float roll);
    void updateBox();

    std::vector<float> matrix_min;
    std::vector<float> matrix_max;
    BoundingBox box;
    float width;
    float height;
    float breadth;
};


#endif //RAYLIB_CPP_EXAMPLE_MYBOUNDINGBOX_H
