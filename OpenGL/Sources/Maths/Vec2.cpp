#include <Maths/Vec2.hpp>

namespace Core::Maths
{
    Vec2::Vec2(const float x, const float y)
        : x(x), y(y)
    {
    }

    Vec2::Vec2(const Vec2& copy)
        : x(copy.x), y(copy.y)
    {
    }

    float Vec2::DotProduct(const Vec2& vec2) const
    {
        return x * vec2.x + y * vec2.y;
    }

    float Vec2::Magnitude() const
    {
        return sqrtf(powf(x, 2) + powf(y, 2));
    }

    float Vec2::CrossProduct(const Vec2& vec2) const
    {
        return x * vec2.y - y * vec2.x;
    }

    Vec2& Vec2::Normalize()
    {
        float magnitude = Magnitude();
        x *= (1 / magnitude);
        y *= (1 / magnitude);
        return *this;
    }

    // Friend Vec2
    Vec2 operator+(const Vec2& left, const Vec2& right)
    {
        return { left.x + right.x, left.y + right.y };
    }

    Vec2 operator-(const Vec2& left, const Vec2& right)
    {
        return { left.x - right.x, left.y - right.y };
    }

    Vec2 operator*(const Vec2& left, const float multiplier)
    {
        return { left.x * multiplier, left.y * multiplier };
    }

    Vec2 operator/(const Vec2& left, const float divider)
    {
        return { left.x / divider, left.y / divider };
    }

    Vec2& operator+=(Vec2& left, const Vec2& right)
    {
        left = left + right;
        return left;
    }

    Vec2& operator-=(Vec2& left, const Vec2& right)
    {
        left = left - right;
        return left;
    }

    Vec2& operator*=(Vec2& left, const float multipler)
    {
        left = left * multipler;
        return left;
    }

    Vec2& operator/=(Vec2& left, const float divider)
    {
        left = left / divider;
        return left;
    }

    bool operator==(const Vec2& left, const Vec2& right)
    {
        if (left.x <= right.x + 0.001f && left.x >= right.x - 0.001f && left.y <= right.y + 0.001f && left.y >= right.y - 0.001f)
            return true;
        else
            return false;
    }

    bool operator!=(const Vec2& left, const Vec2& right)
    {
        if (left.x <= right.x + 0.001f && left.x >= right.x - 0.001f && left.y <= right.y + 0.001f && left.y >= right.y - 0.001f)
            return false;
        else
            return true;
    }

    bool operator<(const Vec2& left, const Vec2& right)
    {
        if (left.x < right.x && left.y < right.y)
            return true;
        else
            return false;
    }

    bool operator<=(const Vec2& left, const Vec2& right)
    {
        if (left.x <= right.x && left.y <= right.y)
            return true;
        else
            return false;
    }

    bool operator>(const Vec2& left, const Vec2& right)
    {
        if (left.x > right.x && left.y > right.y)
            return true;
        else
            return false;
    }

    bool operator>=(const Vec2& left, const Vec2& right)
    {
        if (left.x >= right.x && left.y >= right.y)
            return true;
        else
            return false;
    }
}