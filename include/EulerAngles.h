#ifndef EULERANGLES_EQUALS_EULERANGLES_H_
#define EULERANGLES_EQUALS_EULERANGLES_H_

#include <stddef.h>
#include <ostream>

#include "util.h"

class Quaternion;

class EulerAngles
{
public:
    EulerAngles();
    EulerAngles(double x, double y, double z);
    ~EulerAngles();
    // 設定 X Y Z
    void Set(double x, double y, double z);
    // 與 e2 代表相同旋轉狀態
    bool Equals(const EulerAngles &e2);

    friend class Quaternion;
    friend std::ostream &operator<<(std::ostream &s, const EulerAngles &p);

private:
    double mX;
    double mY;
    double mZ;
};

inline EulerAngles::EulerAngles() : mX(0), mY(0), mZ(0)
{
}

inline EulerAngles::EulerAngles(double x, double y, double z) : mX(x), mY(y), mZ(z)
{
}

inline EulerAngles::~EulerAngles()
{
}

inline void EulerAngles::Set(double x, double y, double z)
{
    mX = x;
    mY = y;
    mZ = z;
}

inline bool EulerAngles::Equals(const EulerAngles &e2)
{
    double x1 = radiansWrap(mX);
    double y1 = radiansWrap(mY);
    double z1 = radiansWrap(mZ);
    double x2 = radiansWrap(e2.mX);
    double y2 = radiansWrap(e2.mY);
    double z2 = radiansWrap(e2.mZ);

    // (x1, y1, z1) -> (x1 + 2nπ, y1 + 2mπ, z1 + 2oπ), n,m,o 皆為整數
    if (closeEnough(x1, x2, 1e-6) &&
        closeEnough(y1, y2, 1e-6) &&
        closeEnough(z1, z2, 1e-6))
    {
        return true;
    }

    // (x1, π/2, z1) -> (x1 - n, π/2, z1 + n), n 為實數
    if (closeEnough(y1, M_PI_2, 1e-6) && closeEnough(y2, M_PI_2, 1e-6))
    {
        double xz = radiansWrap((x1 + z1) - (x2 + z2));
        if (closeEnough(xz, 0.0, 1e-6) || closeEnough(xz, M_PIx2, 1e-6))
        {
            return true;
        }
    }

    // (x1, 3π/2, z1) -> (x1 - n, 3π/2, z1 - n), n 為實數
    if (closeEnough(y1, -M_PI_2, 1e-6) && closeEnough(y2, -M_PI_2, 1e-6))
    {
        double xz = radiansWrap((x1 - z1) - (x2 - z2));
        if (closeEnough(xz, 0.0, 1e-6) || closeEnough(xz, M_PIx2, 1e-6))
        {
            return true;
        }
    }

    // (x1, y1, z1) -> (x1 + π, -y1 + π, z1 - π)
    double y3 = fabs(radiansWrap(y1 + y2));
    if (closeEnough(y3, M_PI, 1e-6))
    {
        double x3 = radiansWrap(x2 + M_PI);
        double z3 = radiansWrap(z2 + M_PI);
        if (closeEnough(x1, x3, 1e-6) && closeEnough(z1, z3, 1e-6))
        {
            return true;
        }
    }

    return false;
}

inline std::ostream &operator<<(std::ostream &s, const EulerAngles &e)
{
    s << "EulerAngles{" << (e.mX * RadToDeg) << ", " << (e.mY * RadToDeg) << ", " << (e.mZ * RadToDeg) << "} (degrees)";
    return s;
}

#endif