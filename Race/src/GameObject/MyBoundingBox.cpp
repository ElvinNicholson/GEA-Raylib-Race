#include "MyBoundingBox.h"

MyBoundingBox::MyBoundingBox(std::vector<float> _min_matrix, float _width, float _height, float _breadth) : matrix_min(_min_matrix), width(_width), height(_height), breadth(_breadth)
{
    matrix_max = matAdd(matrix_min, {width, height, breadth});
    updateBox();
}

std::vector<float> MyBoundingBox::matAdd(std::vector<float> matrix_1, std::vector<float> matrix_2)
{
    std::vector<float> addedMatrix;
    addedMatrix.reserve(3);
    addedMatrix.emplace_back(matrix_1.at(0) + matrix_2.at(0));
    addedMatrix.emplace_back(matrix_1.at(1) + matrix_2.at(1));
    addedMatrix.emplace_back(matrix_1.at(2) + matrix_2.at(2));

    return addedMatrix;
}

std::vector<float> MyBoundingBox::matMul(std::vector<float> matrix_1, std::vector<float> matrix_2)
{

    return std::vector<float>();
}

void MyBoundingBox::rotate(float yaw, float pitch, float roll)
{
    matrix_min = generalRotation(matrix_min, yaw, pitch, roll);
    matrix_max = generalRotation(matrix_max, yaw, pitch, roll);

    updateBox();
}

std::vector<float> MyBoundingBox::generalRotation(std::vector<float> matrix, float yaw, float pitch, float roll)
{
    std::vector<float> rotated;
    rotated.reserve(3);
    rotated.emplace_back(((cos(yaw) * cos(pitch)) * matrix.at(0)) +
                         ((cos(yaw) * sin(pitch) * sin(roll) - sin(yaw) * cos(roll)) * matrix.at(0)) +
                         ((cos(yaw) * sin(pitch) * cos(roll) + sin(yaw) * sin(roll)) * matrix.at(0)));

    rotated.emplace_back(((sin(yaw) * cos(pitch)) * matrix.at(1)) +
                         ((sin(yaw) * sin(pitch) * sin(roll) + cos(yaw) * cos(roll)) * matrix.at(1)) +
                         ((sin(yaw) * sin(pitch) * cos(roll) - cos(yaw) * cos(roll)) * matrix.at(1)));

    rotated.emplace_back(((-sin(pitch)) * matrix.at(2)) +
                         ((cos(pitch) * sin(roll)) * matrix.at(2)) +
                         ((cos(pitch) * cos(roll)) * matrix.at(2)));

    return rotated;
}

std::vector<float> MyBoundingBox::rotateX(std::vector<float> matrix, float angle_deg)
{
    std::vector<float> rotated;
    rotated.reserve(3);
    rotated.emplace_back(matrix.at(0));
    rotated.emplace_back((matrix.at(1) * cos(angle_deg)) + (matrix.at(2) * -sin(angle_deg)));
    rotated.emplace_back((matrix.at(1) * sin(angle_deg)) + (matrix.at(2) * cos(angle_deg)));

    return rotated;
}

std::vector<float> MyBoundingBox::rotateY(std::vector<float> matrix, float angle_deg)
{
    std::vector<float> rotated;
    rotated.reserve(3);
    rotated.emplace_back((matrix.at(0) * cos(angle_deg)) + (matrix.at(2) * sin(angle_deg)));
    rotated.emplace_back(matrix.at(1));
    rotated.emplace_back((matrix.at(0) * -sin(angle_deg)) + (matrix.at(2) * cos(angle_deg)));

    return rotated;
}

BoundingBox MyBoundingBox::matToBox(std::vector<float> _min_matrix, std::vector<float> _max_matrix)
{
    BoundingBox newBox;
    newBox = {{_min_matrix.at(0), _min_matrix.at(1), _min_matrix.at(2)},
              {_max_matrix.at(0), _max_matrix.at(1), _max_matrix.at(2)}};

    return newBox;
}

void MyBoundingBox::updateBox()
{
    box = {{matrix_min.at(0), matrix_min.at(1), matrix_min.at(2)},
           {matrix_max.at(0), matrix_max.at(1), matrix_max.at(2)}};
}

void MyBoundingBox::render()
{
    DrawBoundingBox(box, GREEN);
}
