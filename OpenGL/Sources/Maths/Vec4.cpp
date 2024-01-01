#include <Maths/Vec4.hpp>

namespace Core::Maths
{
    Vec4::Vec4(const float x, const float y, const float z, const float w)
        : x(x), y(y), z(z), w(w)
    {
    }

    Vec4::Vec4(const Vec3 v3, const float w)
        : x(v3.x), y(v3.y), z(v3.z), w(w)
    {
    }

    Vec4::Vec4(const Vec4& copy)
        : x(copy.x), y(copy.y), z(copy.z), w(copy.w)
    {
    }

    float Vec4::DotProduct(const Vec4& vec4) const
    {
        return x * vec4.x + y * vec4.y + z * vec4.z + w * vec4.w;
    }

    float Vec4::Magnitude()
    {
        return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2) + powf(w, 2));
    }

    float Vec4::CrossProduct(const Vec4& vec4) const
    {
        return ((x * vec4.x + x * vec4.y + x * vec4.z + x * vec4.w) + (y * vec4.x + y * vec4.y + y * vec4.z + y * vec4.w) + (z * vec4.x + z * vec4.y + z * vec4.z + z * vec4.w) + (w * vec4.x + w * vec4.y + w * vec4.z + w * vec4.w));
    }

    Vec4& Vec4::Normalize()
    {
        float magnitude = Magnitude();
        x *= (1 / magnitude);
        y *= (1 / magnitude);
        z *= (1 / magnitude);
        w *= (1 / magnitude);
        return *this;
    }

    void Vec4::Homogenize()
    {
        if (w != 0)
        {
            x /= w;
            y /= w;
            z /= w;
            w /= w;
        }
    }

    Vec3 Vec4::toVec3()
    {
        return { x, y, z };
    }

    // Friend Vec4
    Vec4 operator+(const Vec4& left, const Vec4& right)
    {
        return { left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w };
    }

    Vec4 operator-(const Vec4& left, const Vec4& right)
    {
        return { left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w };
    }

    Vec4 operator*(const Vec4& left, const float multiplier)
    {
        return { left.x * multiplier, left.y * multiplier, left.z * multiplier, left.w * multiplier };
    }

    Vec4 operator/(const Vec4& left, const float divider)
    {
        return { left.x / divider, left.y / divider, left.z / divider, left.w / divider };
    }

    Vec4& operator+=(Vec4& left, const Vec4& right)
    {
        left = left + right;
        return left;
    }

    Vec4& operator-=(Vec4& left, const Vec4& right)
    {
        left = left - right;
        return left;
    }

    Vec4& operator*=(Vec4& left, const float multipler)
    {
        left = left * multipler;
        return left;
    }

    Vec4& operator/=(Vec4& left, const float divider)
    {
        left = left / divider;
        return left;
    }

    bool operator==(const Vec4& left, const Vec4& right)
    {
        if (left.x <= right.x + 0.001f && left.x >= right.x - 0.001f && left.y <= right.y + 0.001f && left.y >= right.y - 0.001f && left.z <= right.z + 0.001f && left.z >= right.z - 0.001f && left.w <= right.w + 0.001f && left.w >= right.w - 0.001f)
            return true;
        else
            return false;
    }

    bool operator!=(const Vec4& left, const Vec4& right)
    {
        if (left.x <= right.x + 0.001f && left.x >= right.x - 0.001f && left.y <= right.y + 0.001f && left.y >= right.y - 0.001f && left.z <= right.z + 0.001f && left.z >= right.z - 0.001f && left.w <= right.w + 0.001f && left.w >= right.w - 0.001f)
            return false;
        else
            return true;
    }

    bool operator<(const Vec4& left, const Vec4& right)
    {
        if (left.x < right.x && left.y < right.y && left.z < right.z && left.w < right.w)
            return true;
        else
            return false;
    }

    bool operator<=(const Vec4& left, const Vec4& right)
    {
        if (left.x <= right.x && left.y <= right.y && left.z <= right.z && left.w <= right.w)
            return true;
        else
            return false;
    }

    bool operator>(const Vec4& left, const Vec4& right)
    {
        if (left.x > right.x && left.y > right.y && left.z > right.z && left.w > right.w)
            return true;
        else
            return false;
    }

    bool operator>=(const Vec4& left, const Vec4& right)
    {
        if (left.x >= right.x && left.y >= right.y && left.z >= right.z && left.w >= right.w)
            return true;
        else
            return false;
    }
}