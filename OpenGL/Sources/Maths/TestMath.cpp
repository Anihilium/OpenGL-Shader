#include <Maths/TestMath.hpp>

using namespace Core::Maths;

/////////////////////////////

Mat4 GlmMatToMat(const glm::mat4x4& mat)
{
    return Mat4(mat[0][0], mat[1][0], mat[2][0], mat[3][0], 
                mat[0][1], mat[1][1], mat[2][1], mat[3][1],
                mat[0][2], mat[1][2], mat[2][2], mat[3][2],
                mat[0][3], mat[1][3], mat[2][3], mat[3][3]);
}

void Display(Vec3 vec)
{
    std::cout << "[ " << vec.x << ", " << vec.y << ", " << vec.z << " ]" << std::endl;
}

void Display(Vec4 vec)
{
    std::cout << "[ " << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << " ]" << std::endl;
}

void Display(Mat4 matrix)
{
    for (int i = 0; i < 4; i++)
    {
        std::cout << "| ";
        for (int j = 0; j < 4; j++)
        {
            std::cout << matrix.mat[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
}

void Display(glm::mat4 matrix)
{
    for (int i = 0; i < 4; i++)
    {
        std::cout << "| ";
        for (int j = 0; j < 4; j++)
        {
            std::cout << matrix[j][i] << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
}

////////////////////////////

// ----------------------------------------------------------------------------------
// -------------------------------------- Vec2 --------------------------------------
// ----------------------------------------------------------------------------------

void TestVec2()
{

    // ------------------------------- Operators ------------------------------------
    {
        Vec2 v1(1.f, 1.f);
        Vec2 v2(1.f, 1.f);

        // Operator +
        ASSERT(v1 + v2 == Vec2(2.f, 2.f), "Vector2 Operator+")

        // Operator +=
        v1 += v2;
        ASSERT(v1 == Vec2(2.f, 2.f), "Vector2 Operator+=")

        // Operator -
        ASSERT(v1 - v2 == Vec2(1.f, 1.f), "Vector2 Operator-")

        // Operator -=
        v1 -= v2;
        ASSERT(v1 == Vec2(1.f, 1.f), "Vector2 Operator-=")

        // Operator *
        ASSERT(v1 * 2 == Vec2(2.f, 2.f), "Vector2 Operator*")

        // Operator *=
        v1 *= 2;
        ASSERT(v1 == Vec2(2.f, 2.f), "Vector2 Operator*=")

        // Operator /
        ASSERT(v1 / 2 == Vec2(1.f, 1.f), "Vector2 Operator/")

        // Operator /=
        v1 /= 2;
        ASSERT(v1 == Vec2(1.f, 1.f), "Vector2 Operator/=")

        // Operator <
        ASSERT(v1 < Vec2(1.1f, 1.1f), "Vector2 Operator<")

        // Operator >
        ASSERT(v1 > Vec2(0.9f, 0.9f), "Vector2 Operator>")

        // Operator <=
        ASSERT(v1 <= Vec2(1.f, 1.f), "Vector2 Operator<=")

        // Operator >=
        ASSERT(v1 >= Vec2(1.f, 1.f), "Vector2 Operator>=")

        // Operator ==
        ASSERT(v1 == v2, "Vector2 Operator==")
    }

    // -------------------------- Dot Product ---------------------------------------
    {
        Vec2 v1(1.f, 4.f);
        Vec2 v2(2.f, 3.f);
        glm::vec2 v3(1.f, 4.f);
        glm::vec2 v4(2.f, 3.f);

        ASSERT(v1.DotProduct(v2) == glm::dot(v3, v4), "Vector2 DotProduct")
    }

    // -------------------------- Magnitude -----------------------------------------
    {
        Vec2 v1(4.f, 4.f);
        glm::vec2 v2(4.f, 4.f);
        ASSERT(v1.Magnitude() == glm::length(v2), "Vector2 Magnitude")
    }

    // -------------------------- Cross Product -------------------------------------
    {
        Vec2 v1(5.f, 4.f);
        Vec2 v2(2.f, 3.f);
        ASSERT(v1.CrossProduct(v2) == 7, "Vector2 CrossProduct")
    }

    // -------------------------- Normalize -----------------------------------------
    {
        Vec2 v1(4.f, 4.f);
        glm::vec2 v2(4.f, 4.f);
        float magnitude = v1.Magnitude();
        v1.Normalize();
        ASSERT(v1.x == glm::normalize(v2).x && v1.y == glm::normalize(v2).y, "Vector2 Normalize")
    }
}

// ----------------------------------------------------------------------------------
// -------------------------------------- Vec3 --------------------------------------
// ----------------------------------------------------------------------------------

void TestVec3()
{
    // ------------------------------- Operators ------------------------------------
    {
        Vec3 v1(1.f, 1.f, 1.f);
        Vec3 v2(1.f, 1.f, 1.f);

        // Operator +
        ASSERT(v1 + v2 == Vec3(2.f, 2.f, 2.f ), "Vector3 Operator+")
            
        // Operator +=
        v1 += v2;
        ASSERT(v1 == Vec3(2.f, 2.f, 2.f ), "Vector3 Operator+=")
            
        // Operator -
        ASSERT(v1 - v2 == Vec3(1.f, 1.f, 1.f ), "Vector3 Operator-")
            
        // Operator -=
        v1 -= v2;
        ASSERT(v1 == Vec3(1.f, 1.f, 1.f ), "Vector3 Operator-=")
            
        // Operator *
        ASSERT(v1 * 2 == Vec3(2.f, 2.f, 2.f ), "Vector3 Operator*")
            
        // Operator *=
        v1 *= 2;
        ASSERT(v1 == Vec3(2.f, 2.f, 2.f ), "Vector3 Operator*=")
            
        // Operator /
        ASSERT(v1 / 2 == Vec3(1.f, 1.f, 1.f ), "Vector3 Operator/")
            
        // Operator /=
        v1 /= 2;
        ASSERT(v1 == Vec3(1.f, 1.f, 1.f ), "Vector3 Operator/=")
            
        // Operator <
        ASSERT(v1 < Vec3(1.1f, 1.1f, 1.1f), "Vector3 Operator<")
            
        // Operator >
        ASSERT(v1 > Vec3(0.9f, 0.9f, 0.9f), "Vector3 Operator>")
            
        // Operator <=
        ASSERT(v1 <= Vec3(1.0f, 1.0f, 1.0f ), "Vector3 Operator<=")
            
        // Operator >=
        ASSERT(v1 >= Vec3(1.0f, 1.0f, 1.0f ), "Vector3 Operator>=")
            
        // Operator ==
        ASSERT(v1 == v2, "Vector3 Operator==")
    }

    // -------------------------- Dot Product ---------------------------------------
    {
        Vec3 v1(2.f, 2.f, 2.f);
        Vec3 v2(3.f, 3.f, 3.f);
        glm::vec3 v3(2.f, 2.f, 2.f);
        glm::vec3 v4(3.f, 3.f, 3.f);
        ASSERT(v1.DotProduct(v2) == glm::dot(v3, v4), "Vector3 DotProduct")
    }

    // -------------------------- Magnitude -----------------------------------------
    {
        Vec3 v1(2.f, 2.f, 2.f);
        glm::vec3 v2(2.f, 2.f, 2.f);
        ASSERT(v1.Magnitude() == glm::length(v2), "Vector3 Magnitude")
    }

    // -------------------------- Cross Product -------------------------------------
    {
        Vec3 v1(2.f, 2.f, 2.f);
        Vec3 v2(3.f, 3.f, 3.f);

        glm::vec3 v3(2.f, 2.f, 2.f);
        glm::vec3 v4(3.f, 3.f, 3.f);

        ASSERT(v1.CrossProduct(v2) == Vec3(glm::cross(v3, v4).x, glm::cross(v3, v4).y, glm::cross(v3, v4).z ), "Vector3 CrossProduct")
    }

    // -------------------------- Normalize -----------------------------------------
    {
        Vec3 v1(4.f, 4.f, 4.f);
        glm::vec3 v2(4.f, 4.f, 4.f);
        v1.Normalize();
        ASSERT(v1.x == glm::normalize(v2).x && v1.y == glm::normalize(v2).y && v1.z == glm::normalize(v2).z, "Vector3 Normalize")
    }
}

// ----------------------------------------------------------------------------------
// -------------------------------------- Vec4 --------------------------------------
// ----------------------------------------------------------------------------------


void TestVec4()
{
    // ------------------------------- Operators ------------------------------------
    {
        Vec4 v1(1.f, 1.f, 1.f, 1.f);
        Vec4 v2(1.f, 1.f, 1.f, 1.f);

        // Operator +
        ASSERT(v1 + v2 == Vec4(2.f, 2.f, 2.f, 2.f), "Vec4 Operator+")
            
        // Operator +=
        v1 += v2;
        ASSERT(v1 == Vec4(2.f, 2.f, 2.f, 2.f), "Vec4 Operator+=")
            
        // Operator -
        ASSERT(v1 - v2 == Vec4(1.f, 1.f, 1.f, 1.f), "Vec4 Operator-")
            
        // Operator -=
        v1 -= v2;
        ASSERT(v1 == Vec4(1.f, 1.f, 1.f, 1.f), "Vec4 Operator-=")
            
        // Operator *
        ASSERT(v1 * 2 == Vec4(2.f, 2.f, 2.f, 2.f), "Vec4 Operator*")
            
        // Operator *=
        v1 *= 2;
        ASSERT(v1 == Vec4(2.f, 2.f, 2.f, 2.f), "Vec4 Operator*=")
            
        // Operator /
        ASSERT(v1 / 2 == Vec4(1.f, 1.f, 1.f, 1.f), "Vec4 Operator/")
            
        // Operator /=
        v1 /= 2;
        ASSERT(v1 == Vec4(1.f, 1.f, 1.f, 1.f), "Vec4 Operator/=")
            
        // Operator <
        ASSERT(v1 < Vec4(1.1f, 1.1f, 1.1f, 1.1f), "Vec4 Operator<")
            
        // Operator >
        ASSERT(v1 > Vec4(0.9f, 0.9f, 0.9f, 0.9f), "Vec4 Operator>")
            
        // Operator <=
        ASSERT(v1 <= Vec4(1.0f, 1.0f, 1.0f, 1.0f), "Vec4 Operator<=")
            
        // Operator >=
        ASSERT(v1 >= Vec4(1.0f, 1.0f, 1.0f, 1.f), "Vec4 Operator>=")
            
        // Operator ==
        ASSERT(v1 == v2, "Vec4 Operator==")
        
    }

    // -------------------------- Dot Product ---------------------------------------
    {
        Vec4 v1(2.f, 2.f, 2.f, 2.f);
        Vec4 v2(3.f, 3.f, 3.f, 3.f);
        glm::vec4 v3(2.f, 2.f, 2.f, 2.f);
        glm::vec4 v4(3.f, 3.f, 3.f, 3.f);

        ASSERT(v1.DotProduct(v2) == glm::dot(v3, v4), "Vec4 DotProduct")
    }

    // -------------------------- Magnitude -----------------------------------------
    {
        Vec4 v1(2.f, 2.f, 2.f, 2.f);
        glm::vec4 v2(2.f, 2.f, 2.f, 2.f);
        ASSERT(v1.Magnitude() == glm::length(v2), "Vec4 Magnitude")
    }

    // -------------------------- Normalize -----------------------------------------
    {
        Vec4 v1(4.f, 4.f, 4.f, 4.f);
        glm::vec4 v2(4.f, 4.f, 4.f, 4.f);
        float magnitude = v1.Magnitude();
        v1.Normalize();
        ASSERT(v1.x == glm::normalize(v2).x && v1.y == glm::normalize(v2).y && v1.z == glm::normalize(v2).z && v1.w == glm::normalize(v2).w, "Vec4 Normalize")
    }

    // -------------------------- Homogenize ----------------------------------------
    {
        Vec4 v1(4.f, 4.f, 4.f, 2.f);
        v1.Homogenize();
        ASSERT(v1.x == 2 && v1.y == 2 && v1.z == 2, "Vec4 Homogenize")
    }
}

// ----------------------------------------------------------------------------------
// -------------------------------------- Mat4 --------------------------------------
// ----------------------------------------------------------------------------------

void TestMat4()
{
    // -------------------------- Translation ---------------------------------------
    {
        Mat4 testMat;
        glm::mat4 test = glm::mat4(1.f);
        Vec3 v3 (4.f, 2.f, 5.f);
        glm ::vec3 vec3(4.f, 2.f, 5.f);
        ASSERT(Mat4::CreateTranslationMatrix(v3) == GlmMatToMat(glm::translate(test, vec3)), "Mat4 Translation")
    }

    // -------------------------- Identity ------------------------------------------
    {
        ASSERT(Mat4::Identity() == GlmMatToMat(glm::mat4(1.f)), "Mat4 Identity")

            glm::mat4 m1 = glm::mat4(1.f, 2.f, 3.f, 4.f,
                1.f, 2.f, 3.f, 4.f,
                1.f, 2.f, 3.f, 4.f,
                1.f, 2.f, 3.f, 4.f);

        // -------------------------- Addition --------------------------------------
        ASSERT(GlmMatToMat(m1) + Mat4::Identity() == GlmMatToMat(glm::mat4(1.f) + m1), "Mat4 Addition")

            glm::mat4 m2 = glm::mat4(1.f, 2.f, 3.f, 0.f,
                6.f, 2.f, 3.f, 4.f,
                8.f, 2.f, 5.f, 4.f,
                9.f, 2.f, 3.f, 4.f);

        // -------------------------- Multiplication --------------------------------
        ASSERT(GlmMatToMat(m1) * GlmMatToMat(m2) == GlmMatToMat(m1 * m2), "Mat4 Multiplication")

        // -------------------------- Transpose -------------------------------------
        ASSERT(GlmMatToMat(m1).Transpose() == GlmMatToMat(glm::transpose(m1)), "Mat4 Transpose")
    }


    // -------------------------- Rotation ------------------------------------------
    {
        glm::mat4x4 mat(1.f, 2.f, 3.f, 4.f,
                        1.f, 2.f, 3.f, 4.f,
                        1.f, 2.f, 3.f, 4.f,
                        1.f, 2.f, 3.f, 4.f);

        ASSERT(GlmMatToMat(mat) * Mat4::CreateXRotationMatrix(90.f) == GlmMatToMat(glm::rotate(mat, (float)M_PI_2, { 1.f, 0.f, 0.f })), "Mat4 Xrotation")
    
        ASSERT(GlmMatToMat(mat) * Mat4::CreateYRotationMatrix(90.f) == GlmMatToMat(glm::rotate(mat, (float)M_PI_2, { 0.f, 1.f, 0.f })), "Mat4 Yrotation")

        ASSERT(GlmMatToMat(mat) * Mat4::CreateZRotationMatrix(90.f) == GlmMatToMat(glm::rotate(mat, (float)M_PI_2, { 0.f, 0.f, 1.f })), "Mat4 Zrotation")

        // -------------------------- Scale -----------------------------------------
        ASSERT(GlmMatToMat(mat) * Mat4::CreateScaleMatrix(Vec3(2.f, 2.f, 2.f)) == GlmMatToMat(glm::scale(mat, glm::vec3(2.f, 2.f, 2.f))), "Mat4 Scale")


    }

    // -------------------------- Operators -----------------------------------------
    {
        glm::mat4 mat1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        glm::mat4 mat2 = glm::mat4(mat1);

        // Operator ==
        ASSERT(GlmMatToMat(mat1) == GlmMatToMat(mat2), "Mat4 Operator==")

        // Operator +
        ASSERT(GlmMatToMat(mat1) + GlmMatToMat(mat2) == GlmMatToMat(mat1 + mat2), "Mat4 Operator+")

        // Operator -
        ASSERT(GlmMatToMat(mat1) - GlmMatToMat(mat2) == GlmMatToMat(mat1 - mat2), "Mat4 Operator-")

        // Operator* Mat4
        ASSERT(GlmMatToMat(mat1) * GlmMatToMat(mat2) == GlmMatToMat(mat1 * mat2), "Mat4 Operator* Mat4")

        // Operator* Vec4
        glm::vec4 resVec = mat1 * glm::vec4(2.f, 2.f, 2.f, 2.f);
        ASSERT(GlmMatToMat(mat1) * Vec4(2.f, 2.f, 2.f, 2.f) == Vec4(resVec.x, resVec.y, resVec.z, resVec.w), "Mat4 Operator* Vec4")
    }

    // -------------------------- Determinant ---------------------------------------
    {
        glm::mat4 detTest(1.f, 2.f, 3.f, 4.f,
                          2.f, 3.f, 4.f, 1.f,
                          3.f, 4.f, 1.f, 2.f,
                          4.f, 1.f, 2.f, 3.f);

        ASSERT(glm::determinant(detTest) == GlmMatToMat(detTest).Determinant(), "Mat4 Determinant")

        // -------------------------- Inverse ---------------------------------------
        ASSERT(GlmMatToMat(glm::inverse(detTest)) == GlmMatToMat(detTest).GetInverse(), "Mat4 Inverse")
    }
}

void MathTests()
{
    TestVec2();
    TestVec3();
    TestVec4();
    TestMat4();
}