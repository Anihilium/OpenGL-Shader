#pragma once
#include <cmath>
#include <Maths/Vec3.hpp>
#include <Maths/Vec4.hpp>

#define M_PI    3.1415926f
#define M_PI_2  1.5707963f

namespace Core::Maths
{
    class Mat4 //Rows then Columns
    {
    public:
        float mat[4][4];

        Mat4();
        Mat4(const Mat4& other);
        Mat4(const float elements[16]);
        Mat4(const float f1, const float f2, const float f3, const float f4,
            const float f5, const float f6, const float f7, const float f8,
            const float f9, const float f10, const float f11, const float f12,
            const float f13, const float f14, const float f15, const float f16);
        ~Mat4() {}

        static Mat4 Identity();

        Mat4 Transpose();
        Mat4 GetInverse() const;

        float Determinant() const;
        Mat4 CofactorMatrix() const;

        Mat4 operator+(const Mat4& other);
        Mat4 operator-(const Mat4& other);
        Mat4 operator*(const Mat4& other);
        Vec4 operator*(const Vec4& other);
        Mat4 operator*(const float other);

        static Mat4 CreateTranslationMatrix(const Vec3& translation);
        static Mat4 CreateScaleMatrix(const Vec3& scale);
        static Mat4 CreateXRotationMatrix(float angle);
        static Mat4 CreateYRotationMatrix(float angle);
        static Mat4 CreateZRotationMatrix(float angle);

        static Mat4 CreateTransformationMatrix(const Vec3& translation, const Vec3& scale, const Vec3& rotation);
    };

    bool operator==(const Mat4& left, const Mat4& right);
}
