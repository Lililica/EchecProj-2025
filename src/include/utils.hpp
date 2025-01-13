#ifndef UTILS_HPP
#define UTILS_HPP

template<typename T>
struct Vec2 {
    T x;
    T y;

    Vec2()
        : x(0), y(0) {}
    Vec2(T x, T y)
        : x(x), y(y) {}

    Vec2 operator+(const Vec2& other) const
    {
        return {x + other.x, y + other.y};
    }

    Vec2 operator-(const Vec2& other) const
    {
        return {x - other.x, y - other.y};
    }

    Vec2 operator*(T scalar) const
    {
        return {x * scalar, y * scalar};
    }

    Vec2 operator/(T scalar) const
    {
        return {x / scalar, y / scalar};
    }

    bool operator==(const Vec2& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vec2& other) const
    {
        return !(*this == other);
    }
};

template<typename T>
struct Vec3 {
    T x;
    T y;
    T z;

    Vec3()
        : x(0), y(0), z(0) {}
    Vec3(T x, T y, T z)
        : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& other) const
    {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vec3 operator-(const Vec3& other) const
    {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vec3 operator*(T scalar) const
    {
        return {x * scalar, y * scalar, z * scalar};
    }

    Vec3 operator/(T scalar) const
    {
        return {x / scalar, y / scalar, z / scalar};
    }

    bool operator==(const Vec3& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Vec3& other) const
    {
        return !(*this == other);
    }
};

#endif // UTILS_HPP