#include <Maths/Mat4.hpp>

namespace Core::Maths
{
    Mat4::Mat4()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat[i][j] = 0.f;
            }
        }
    }

    Mat4::Mat4(const Mat4& other)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat[i][j] = other.mat[i][j];
            }
        }
    }

    Mat4::Mat4(const float elements[16])
    {
        for (int i = 0; i < 16; ++i)
            mat[i/4][i%4] = elements[i];
    }

    Mat4::Mat4(const float f1, const float f2, const float f3, const float f4,
        const float f5, const float f6, const float f7, const float f8,
        const float f9, const float f10, const float f11, const float f12,
        const float f13, const float f14, const float f15, const float f16)
    {
        mat[0][0] = f1;  mat[0][1] = f2;  mat[0][2] = f3;  mat[0][3] = f4;
        mat[1][0] = f5;  mat[1][1] = f6;  mat[1][2] = f7;  mat[1][3] = f8;
        mat[2][0] = f9;  mat[2][1] = f10; mat[2][2] = f11; mat[2][3] = f12;
        mat[3][0] = f13; mat[3][1] = f14; mat[3][2] = f15; mat[3][3] = f16;
    }

    Mat4 Mat4::Identity()
    {
        Mat4 identity;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (i == j)
                    identity.mat[i][j] = 1.f;
            }
        }
        return identity;
    }

    Mat4 Mat4::Transpose()
    {
        Mat4 transpose;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                transpose.mat[i][j] = mat[j][i];
            }
        }
        return transpose;
    }

    Mat4 Mat4::GetInverse() const
    {
        Mat4 inverse;
        float determinant = Determinant();
        if (determinant == 0)
            return Mat4::Identity();
        Mat4 cofactorMatrix = CofactorMatrix();
        cofactorMatrix.Transpose();
        cofactorMatrix = cofactorMatrix * (1.f / determinant);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                inverse.mat[i][j] = cofactorMatrix.mat[i][j];
            }
        }
        return inverse;
    }

    float Mat4::Determinant() const
    {
        return mat[0][0] * (mat[1][1] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - mat[1][2] * (mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3]) + mat[1][3] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]))
            - mat[0][1] * (mat[1][0] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - mat[1][2] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]) + mat[1][3] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0]))
            + mat[0][2] * (mat[1][0] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) - mat[1][1] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]) + mat[1][3] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]))
            - mat[0][3] * (mat[1][0] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]) - mat[1][1] * (mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2]) + mat[1][2] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]));
    }

    Mat4 Mat4::CofactorMatrix() const
    {
        Mat4 Cof;

        Cof.mat[0][0] = mat[1][1] * (mat[2][2] * mat[3][3] - mat[3][2] * mat[2][3]) - mat[1][2] * (mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3]) + mat[1][3] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]);
        Cof.mat[0][1] = -(mat[1][0] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - mat[1][2] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]) + mat[1][3] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0]));
        Cof.mat[0][2] = mat[1][0] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) - mat[1][1] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]) + mat[1][3] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]);
        Cof.mat[0][3] = -(mat[1][0] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]) - mat[1][1] * (mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2]) + mat[1][2] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]));

        Cof.mat[1][0] = -(mat[0][1] * (mat[2][2] * mat[3][3] - mat[3][2] * mat[2][3]) - mat[0][2] * (mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3]) + mat[0][3] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]));
        Cof.mat[1][1] = mat[0][0] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - mat[0][2] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]) + mat[0][3] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0]);
        Cof.mat[1][2] = -(mat[0][0] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) - mat[0][1] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]) + mat[0][3] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]));
        Cof.mat[1][3] = mat[0][0] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]) - mat[0][1] * (mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2]) + mat[0][2] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]);

        Cof.mat[2][0] = mat[0][1] * (mat[1][2] * mat[3][3] - mat[3][2] * mat[1][3]) - mat[0][2] * (mat[1][1] * mat[3][3] - mat[3][1] * mat[1][3]) + mat[0][3] * (mat[1][1] * mat[3][2] - mat[1][2] * mat[3][1]);
        Cof.mat[2][1] = -(mat[0][0] * (mat[1][2] * mat[3][3] - mat[1][3] * mat[3][2]) - mat[0][2] * (mat[1][0] * mat[3][3] - mat[3][0] * mat[1][3]) + mat[0][3] * (mat[1][0] * mat[3][2] - mat[1][2] * mat[3][0]));
        Cof.mat[2][2] = mat[0][0] * (mat[1][1] * mat[3][3] - mat[1][3] * mat[3][1]) - mat[0][1] * (mat[1][0] * mat[3][3] - mat[3][0] * mat[1][3]) + mat[0][3] * (mat[1][0] * mat[3][1] - mat[1][1] * mat[3][0]);
        Cof.mat[2][3] = -(mat[0][0] * (mat[1][1] * mat[3][2] - mat[1][2] * mat[3][1]) - mat[0][1] * (mat[1][0] * mat[3][2] - mat[3][0] * mat[1][2]) + mat[0][2] * (mat[1][0] * mat[3][1] - mat[1][1] * mat[3][0]));

        Cof.mat[3][0] = -(mat[0][1] * (mat[1][2] * mat[2][3] - mat[2][2] * mat[1][3]) - mat[0][2] * (mat[1][1] * mat[2][3] - mat[2][1] * mat[1][3]) + mat[0][3] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]));
        Cof.mat[3][1] = mat[0][0] * (mat[1][2] * mat[2][3] - mat[1][3] * mat[2][2]) - mat[0][2] * (mat[1][0] * mat[2][3] - mat[2][0] * mat[1][3]) + mat[0][3] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]);
        Cof.mat[3][2] = -(mat[0][0] * (mat[1][1] * mat[2][3] - mat[1][3] * mat[2][1]) - mat[0][1] * (mat[1][0] * mat[2][3] - mat[2][0] * mat[1][3]) + mat[0][3] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]));
        Cof.mat[3][3] = mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) - mat[0][1] * (mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]) + mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);

        return Cof;
    }

    Mat4 Mat4::CreateTranslationMatrix(const Vec3& translation)
    {
        Mat4 translationMatrix = Mat4::Identity();
        if (translation.x != 0.f)
            translationMatrix.mat[0][3] = translation.x;
        if (translation.y != 0.f)
            translationMatrix.mat[1][3] = translation.y;
        if (translation.z != 0.f)
            translationMatrix.mat[2][3] = translation.z;
        return translationMatrix;
    }

    Mat4 Mat4::CreateScaleMatrix(const Vec3& scale)
    {
        Mat4 scaleMatrix;
        scaleMatrix.mat[0][0] = scale.x;
        scaleMatrix.mat[1][1] = scale.y;
        scaleMatrix.mat[2][2] = scale.z;
        scaleMatrix.mat[3][3] = 1.f;
        return scaleMatrix;
    }

    Mat4 Mat4::CreateXRotationMatrix(float angle)
    {
        angle *= M_PI / 180.f;
        Mat4 xRotationMatrix = Mat4::Identity();
        xRotationMatrix.mat[1][1] = cosf(angle);
        xRotationMatrix.mat[1][2] = -sinf(angle);
        xRotationMatrix.mat[2][1] = sinf(angle);
        xRotationMatrix.mat[2][2] = cosf(angle);
        return xRotationMatrix;
    }

    Mat4 Mat4::CreateYRotationMatrix(float angle)
    {
        angle *= M_PI / 180.f;
        Mat4 yRotationMatrix = Mat4::Identity();
        yRotationMatrix.mat[0][0] = cosf(angle);
        yRotationMatrix.mat[0][2] = sinf(angle);
        yRotationMatrix.mat[2][0] = -sinf(angle);
        yRotationMatrix.mat[2][2] = cosf(angle);
        return yRotationMatrix;
    }

    Mat4 Mat4::CreateZRotationMatrix(float angle)
    {
        angle *= M_PI / 180.f;
        Mat4 zRotationMatrix = Mat4::Identity();
        zRotationMatrix.mat[0][0] = cosf(angle);
        zRotationMatrix.mat[0][1] = -sinf(angle);
        zRotationMatrix.mat[1][0] = sinf(angle);
        zRotationMatrix.mat[1][1] = cosf(angle);
        return zRotationMatrix;
    }

    Mat4 Mat4::CreateTransformationMatrix(const Vec3& translation, const Vec3& scale, const Vec3& rotation)
    {
        return CreateTranslationMatrix(translation) * CreateYRotationMatrix(rotation.y) * CreateXRotationMatrix(rotation.x) * CreateZRotationMatrix(rotation.z) * CreateScaleMatrix(scale);
    }

    Mat4 Mat4::operator+(const Mat4& other)
    {
        Mat4 res;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                res.mat[i][j] = mat[i][j] + other.mat[i][j];
            }
        }
        return res;
    }

    Mat4 Mat4::operator-(const Mat4& other)
    {
        Mat4 res;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                res.mat[i][j] = mat[i][j] - other.mat[i][j];
            }
        }
        return res;
    }

    Mat4 Mat4::operator*(const Mat4& other)
    {
        Mat4 res;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    res.mat[i][j] += mat[i][k] * other.mat[k][j];
                }
            }
        }
        return res;
    }

    Vec4 Mat4::operator*(const Vec4& other)
    {
        Vec4 res;
        res.x = mat[0][0] * other.x + mat[0][1] * other.y + mat[0][2] * other.z + mat[0][3] * other.w;
        res.y = mat[1][0] * other.x + mat[1][1] * other.y + mat[1][2] * other.z + mat[1][3] * other.w;
        res.z = mat[2][0] * other.x + mat[2][1] * other.y + mat[2][2] * other.z + mat[2][3] * other.w;
        res.w = mat[3][0] * other.x + mat[3][1] * other.y + mat[3][2] * other.z + mat[3][3] * other.w;
        return res;
    }

    Mat4 Mat4::operator*(const float other)
    {
        Mat4 res;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                res.mat[i][j] = mat[i][j] * other;
            }
        }
        return res;
    }

    bool operator==(const Mat4& left, const Mat4& right)
    {
        float margin = 0.000001f;
        bool res = true;

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (left.mat[i][j] > right.mat[i][j] + margin || left.mat[i][j] < right.mat[i][j] - margin)
                {
                    res = false;
                    break;
                }
            }
            if (res == false)
                break;
        }
        return res;
    }
}