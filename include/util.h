#ifndef EULERANGLES_EQUALS_UTIL_H_
#define EULERANGLES_EQUALS_UTIL_H_

#include <algorithm>
#include <cmath>

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502884L // π
#endif
#ifndef M_PI_2
#define M_PI_2 1.570796326794896619231321691639751442L // π/2
#endif
#ifndef M_PI_2x3
#define M_PI_2x3 ((M_PI_2)*3.0) // 1.5π 
#endif
#ifndef M_PIx2
#define M_PIx2 ((M_PI)*2.0) // 2π
#endif

// 將 value 限制於 [max, min]
inline double clamp(double value, double min, double max)
{
    return std::max(min, std::min(max, value));
}

// 四捨五入至小數點下第六位
inline double round6(double v)
{
    return round(v * 1000000) / 1000000;
}

// 將弧度轉為角度
#define RadToDeg (180.0 / M_PI)
// 將角度轉為弧度
#define DegToRad (M_PI / 180.0)

// 將弧度轉換至範圍 (-π, π]
inline double radiansWrap(double r)
{
    for (; r > M_PI;)
    {
        r -= M_PIx2;
    }
    for (; r <= -M_PI;)
    {
        r += M_PIx2;
    }
    return r;
}

// 判斷兩浮點數 v1 v2 是差值是否小於等於 range
inline bool closeEnough(double v1, double v2, double range)
{
    return fabs(v1 - v2) <= range;
}

#endif
