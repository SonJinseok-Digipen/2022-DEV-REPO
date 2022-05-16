#include"TransformMatrix.h"
#include <cmath>

math::TransformMatrix::TransformMatrix()
{
    Reset();
}

math::TransformMatrix math::TransformMatrix::operator * (TransformMatrix rhs) const
{
    TransformMatrix result;

    result.matrix[0][0] = matrix[0][0] * rhs[0][0] + matrix[0][1] * rhs[1][0] + matrix[0][2] * rhs[2][0];
    result.matrix[0][1] = matrix[0][0] * rhs[0][1] + matrix[0][1] * rhs[1][1] + matrix[0][2] * rhs[2][1];
    result.matrix[0][2] = matrix[0][0] * rhs[0][2] + matrix[0][1] * rhs[1][2] + matrix[0][2] * rhs[2][2];
    result.matrix[1][0] = matrix[1][0] * rhs[0][0] + matrix[1][1] * rhs[1][0] + matrix[1][2] * rhs[2][0];
    result.matrix[1][1] = matrix[1][0] * rhs[0][1] + matrix[1][1] * rhs[1][1] + matrix[1][2] * rhs[2][1];
    result.matrix[1][2] = matrix[1][0] * rhs[0][2] + matrix[1][1] * rhs[1][2] + matrix[1][2] * rhs[2][2];
    result.matrix[2][0] = matrix[2][0] * rhs[0][0] + matrix[2][1] * rhs[1][0] + matrix[2][2] * rhs[2][0];
    result.matrix[2][1] = matrix[2][0] * rhs[0][1] + matrix[2][1] * rhs[1][1] + matrix[2][2] * rhs[2][1];
    result.matrix[2][2] = matrix[2][0] * rhs[0][2] + matrix[2][1] * rhs[1][2] + matrix[2][2] * rhs[2][2];

    return result;
}

math::TransformMatrix& math::TransformMatrix::operator *= (math::TransformMatrix rhs) 
{
    (*this) = (*this) * rhs;
    return (*this);
}

void math::TransformMatrix::Reset()
{
    matrix[0][0] = 1;   matrix[0][1] = 0;   matrix[0][2] = 0;
    matrix[1][0] = 0;   matrix[1][1] = 1;   matrix[1][2] = 0;
    matrix[2][0] = 0;   matrix[2][1] = 0;   matrix[2][2] = 1;
}

math::vec2 math::TransformMatrix::operator*(vec2 rhs) const
{
    math::vec2 result;
    result.x = matrix[0][0] * rhs.x + matrix[0][1] * rhs.y + matrix[0][2];
    result.y = matrix[1][0] * rhs.x + matrix[1][1] * rhs.y + matrix[1][2];
    return result;

}

math::TranslateMatrix::TranslateMatrix(ivec2 translate)
{

    matrix[0][0] = 1;   matrix[0][1] = 0;   matrix[0][2] = translate.x;
    matrix[1][0] = 0;   matrix[1][1] = 1;   matrix[1][2] = translate.y;
    matrix[2][0] = 0;   matrix[2][1] = 0;   matrix[2][2] = 1;
}

math::TranslateMatrix::TranslateMatrix(vec2 translate)
{
    matrix[0][0] = 1;   matrix[0][1] = 0;   matrix[0][2] = translate.x;
    matrix[1][0] = 0;   matrix[1][1] = 1;   matrix[1][2] = translate.y;
    matrix[2][0] = 0;   matrix[2][1] = 0;   matrix[2][2] = 1;
}

math::RotateMatrix::RotateMatrix(double radians)
{
    matrix[0][0] = std::cos(radians);   matrix[0][1] = -1*std::sin(radians);   matrix[0][2] = 0;
    matrix[1][0] = std::sin(radians);   matrix[1][1] = std::cos(radians);      matrix[1][2] = 0;
    matrix[2][0] = 0;                      matrix[2][1] = 0;                        matrix[2][2] = 1;
}

math::ScaleMatrix::ScaleMatrix(vec2 scale)
{
    matrix[0][0] = scale.x;           matrix[0][1] = 0;            matrix[0][2] = 0;
    matrix[1][0] = 0;                 matrix[1][1] = scale.y;      matrix[1][2] = 0;
    matrix[2][0] = 0;                 matrix[2][1] = 0;            matrix[2][2] = 1;
}