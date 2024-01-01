#include <Maths/Vec3.hpp>

namespace Core::Maths
{
    // ----------------------------------------------------------------------------------
    // -------------------------------------- Vec3 --------------------------------------
    // ----------------------------------------------------------------------------------

    Vec3::Vec3(const float x, const float y, const float z)
        : x(x), y(y), z(z)
    {
    }

    Vec3::Vec3(const Vec3& copy)
        : x(copy.x), y(copy.y), z(copy.z)
    {
    }

    float Vec3::DotProduct(const Vec3& vec3) const
    {
        return x * vec3.x + y * vec3.y + z * vec3.z;
    }

    float Vec3::Magnitude() const
    {
        return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
    }

    Vec3 Vec3::CrossProduct(const Vec3& vec3) const
    {
        return { (y * vec3.z) - (z * vec3.y), (z * vec3.x) - (x * vec3.z), (x * vec3.y) - (y * vec3.x) };
    }

    Vec3& Vec3::Normalize()
    {
        float magnitude = Magnitude();
        x *= (1 / magnitude);
        y *= (1 / magnitude);
        z *= (1 / magnitude);
        return *this;
    }

    // Friend Vec3
    Vec3 operator+(const Vec3& left, const Vec3& right)
    {
        return { left.x + right.x, left.y + right.y, left.z + right.z };
    }

    Vec3 operator-(const Vec3& left, const Vec3& right)
    {
        return { left.x - right.x, left.y - right.y, left.z - right.z };
    }

    Vec3 operator-(const Vec3 right)
    {
        return { -right.x, -right.y, -right.z };
    }

    Vec3 operator*(const Vec3& left, const float multiplier)
    {
        return { left.x * multiplier, left.y * multiplier, left.z * multiplier };
    }

    Vec3 operator/(const Vec3& left, const float divider)
    {
        return { left.x / divider, left.y / divider, left.z / divider };
    }

    Vec3& operator+=(Vec3& left, const Vec3& right)
    {
        left = left + right;
        return left;
    }

    Vec3& operator-=(Vec3& left, const Vec3& right)
    {
        left = left - right;
        return left;
    }

    Vec3& operator*=(Vec3& left, const float multipler)
    {
        left = left * multipler;
        return left;
    }

    Vec3& operator/=(Vec3& left, const float divider)
    {
        left = left / divider;
        return left;
    }

    bool operator==(const Vec3& left, const Vec3& right)
    {
        if (left.x <= right.x + 0.001f && left.x >= right.x - 0.001f && left.y <= right.y + 0.001f && left.y >= right.y - 0.001f && left.z <= right.z + 0.001f && left.z >= right.z - 0.001f)
            return true;
        else
            return false;
    }

    bool operator!=(const Vec3& left, const Vec3& right)
    {
        if (left.x <= right.x + 0.001f && left.x >= right.x - 0.001f && left.y <= right.y + 0.001f && left.y >= right.y - 0.001f && left.z <= right.z + 0.001f && left.z >= right.z - 0.001f)
            return false;
        else
            return true;
    }

    bool operator<(const Vec3& left, const Vec3& right)
    {
        if (left.x < right.x && left.y < right.y && left.z < right.z)
            return true;
        else
            return false;
    }

    bool operator<=(const Vec3& left, const Vec3& right)
    {
        if (left.x <= right.x && left.y <= right.y && left.z <= right.z)
            return true;
        else
            return false;
    }

    bool operator>(const Vec3& left, const Vec3& right)
    {
        if (left.x > right.x && left.y > right.y && left.z > right.z)
            return true;
        else
            return false;
    }

    bool operator>=(const Vec3& left, const Vec3& right)
    {
        if (left.x >= right.x && left.y >= right.y && left.z >= right.z)
            return true;
        else
            return false;
    }
}