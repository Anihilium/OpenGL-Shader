#pragma once
#include <cmath>

namespace Core::Maths
{
    class Vec3
    {
    public:
        float x;
        float y;
        float z;

        Vec3(const float x = 0.f, const float y = 0.f, const float z = 0.f);
        Vec3(const Vec3& copy);

        float DotProduct(const Vec3& vec3) const;
        float Magnitude() const;
        Vec3 CrossProduct(const Vec3& vec3) const;
        Vec3& Normalize();

        friend Vec3 operator+(const Vec3& left, const Vec3& right);
        friend Vec3 operator-(const Vec3& left, const Vec3& right);
        friend Vec3 operator-(const Vec3 right);
        friend Vec3 operator*(const Vec3& left, const float multiplier);
        friend Vec3 operator/(const Vec3& left, const float divider);

        friend Vec3& operator+=(Vec3& left, const Vec3& right);
        friend Vec3& operator-=(Vec3& left, const Vec3& right);
        friend Vec3& operator*=(Vec3& left, const float multipler);
        friend Vec3& operator/=(Vec3& left, const float divider);

        friend bool operator==(const Vec3& left, const Vec3& right);
        friend bool operator!=(const Vec3& left, const Vec3& right);

        friend bool operator<(const Vec3& left, const Vec3& right);
        friend bool operator<=(const Vec3& left, const Vec3& right);
        friend bool operator>(const Vec3& left, const Vec3& right);
        friend bool operator>=(const Vec3& left, const Vec3& right);
    };

    // Friends Vec3
    Vec3 operator+(const Vec3& left, const Vec3& right);
    Vec3 operator-(const Vec3& left, const Vec3& right);
    Vec3 operator-(const Vec3 right);
    Vec3 operator*(const Vec3& Vec3, const float multiplier);
    Vec3 operator/(const Vec3& left, const float divider);

    Vec3& operator+=(Vec3& left, const Vec3& right);
    Vec3& operator-=(Vec3& left, const Vec3& right);
    Vec3& operator*=(Vec3& left, const float multipler);
    Vec3& operator/=(Vec3& left, const float divider);

    bool operator==(const Vec3& left, const Vec3& right);
    bool operator!=(const Vec3& left, const Vec3& right);

    bool operator<(const Vec3& left, const Vec3& right);
    bool operator<=(const Vec3& left, const Vec3& right);
    bool operator>(const Vec3& left, const Vec3& right);
    bool operator>=(const Vec3& left, const Vec3& right);
}