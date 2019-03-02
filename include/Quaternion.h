#ifndef EULERANGLES_EQUALS_QUATERNION_H_
#define EULERANGLES_EQUALS_QUATERNION_H_

#include "EulerAngles.h"
#include "util.h"

// 四元數
class Quaternion
{
public:
    Quaternion();
    // 將歐拉角轉為四元數，這裡順序是 XYZ
    Quaternion(const EulerAngles &e);
    ~Quaternion();
    // 從歐拉角轉換為四元數
    void FromEuler(const EulerAngles &e);
    // 內積
    double Dot(const Quaternion &q);
    // 夾角弧度
    double Angle(const Quaternion &q);

private:
    double mX;
    double mY;
    double mZ;
    double mW;
};

inline Quaternion::Quaternion() : mX(0), mY(0), mZ(0), mW(1)
{
}

inline Quaternion::Quaternion(const EulerAngles &e)
{
    FromEuler(e);
}

inline Quaternion::~Quaternion()
{
}

inline void Quaternion::FromEuler(const EulerAngles &e)
{
    double c1 = cos(e.mX / 2);
    double c2 = cos(e.mY / 2);
    double c3 = cos(e.mZ / 2);

    double s1 = sin(e.mX / 2);
    double s2 = sin(e.mY / 2);
    double s3 = sin(e.mZ / 2);

    mX = s1 * c2 * c3 + c1 * s2 * s3;
    mY = c1 * s2 * c3 - s1 * c2 * s3;
    mZ = c1 * c2 * s3 + s1 * s2 * c3;
    mW = c1 * c2 * c3 - s1 * s2 * s3;
}

inline double Quaternion::Dot(const Quaternion &q)
{
    return mX * q.mX + mY * q.mY + mZ * q.mZ + mW * q.mW;
}

inline double Quaternion::Angle(const Quaternion &q)
{
    return acos(abs(clamp(Dot(q), -1.0, 1.0))) * 2.0;
}

#endif